/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 07:56:56 by bkael             #+#    #+#             */
/*   Updated: 2021/11/21 07:57:13 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_next_pipe(int *fd1, int *fd2, int next)
{
	if (next)
	{
		close(fd1[0]);
		close(fd1[1]);
		fd1[0] = fd2[0];
		fd1[1] = fd2[1];
		pipe(fd2);
	}
	else
	{
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
	}
}

void	ft_run_fork(t_p *arg, char **tokens, int st)
{
	int		i;

	if (arg->start)
		dup2(arg->fd1[0], 0);
	if (!arg->last)
		dup2(arg->fd2[1], 1);
	ft_next_pipe(arg->fd1, arg->fd2, 0);
	arg->copy = (char **)malloc(sizeof(char *) * (arg->end + 1));
	if (!arg->copy)
	{
		ft_putendl_fd("Malloc error in child process", 2);
		g_code = 1;
		ft_free_exit(arg->tokens, arg->c_env, arg->cmd, arg->prompt);
	}
	i = -1;
	while (++i < arg->end)
		arg->copy[i] = ft_strndup(tokens[st + i], ft_strlen(tokens[st + i]));
	arg->copy[i] = NULL;
	ft_start_exec(&arg->copy, arg->c_env, arg->cmd, arg->prompt);
	ft_free_tokens(arg->copy);
	ft_free_exit(arg->tokens, arg->c_env, arg->cmd, arg->prompt);
}

int	ft_run_pipe(t_p *arg)
{
	while ((*arg->tokens)[arg->start])
	{
		arg->end = 0;
		while ((*arg->tokens)[arg->start + arg->end]
			&& ft_strcmp((*arg->tokens)[arg->start + arg->end], "|"))
			arg->end++;
		if (!ft_strcmp((*arg->tokens)[arg->start + arg->end], "|"))
			arg->last = 0;
		else
			arg->last = 1;
		signal(SIGINT, SIG_IGN);
		arg->pid = fork();
		if (arg->pid == -1)
			return (-1);
		else if (arg->pid == 0)
			ft_run_fork(arg, *arg->tokens, arg->start);
		arg->children++;
		ft_next_pipe(arg->fd1, arg->fd2, 1);
		if (!ft_strcmp((*arg->tokens)[arg->start + arg->end], "|"))
			arg->start += arg->end + 1;
		else
			arg->start += arg->end;
	}
	return (arg->children);
}

int	ft_init_pipes(int *fd1, int *fd2)
{
	if (pipe(fd1) == -1)
	{
		ft_putendl_fd("Pipe error", 2);
		g_code = 1;
		return (1);
	}
	if (pipe(fd2) == -1)
	{
		close(fd1[0]);
		close(fd1[1]);
		ft_putendl_fd("Pipe error", 2);
		g_code = 1;
		return (1);
	}
	return (0);
}

int	ft_check_pipe(char ***tokens, char ***c_env, char *cmd, char *prompt)
{
	int	i;
	t_p	arg;

	i = 0;
	while ((*tokens)[i] && ft_strcmp((*tokens)[i], "|"))
		i++;
	if (!(*tokens)[i])
		return (ft_start_exec(tokens, c_env, cmd, prompt));
	arg = ft_init_arg(tokens, c_env, cmd, prompt);
	if (ft_init_pipes(arg.fd1, arg.fd2))
		return (1);
	arg.children = ft_run_pipe(&arg);
	if (arg.children == -1)
	{
		ft_next_pipe(arg.fd1, arg.fd2, 0);
		return (ft_print_error("Fork error", 1));
	}
	while (arg.children--)
		wait(&g_code);
	g_code = WEXITSTATUS(g_code);
	ft_next_pipe(arg.fd1, arg.fd2, 0);
	dup2(arg.save_in, 0);
	close(arg.save_in);
	return (1);
}
