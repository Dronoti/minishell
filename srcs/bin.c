/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 07:56:45 by bkael             #+#    #+#             */
/*   Updated: 2021/11/30 07:57:39 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_start_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_code(void)
{
	if (g_code == 2)
		g_code = 130;
	else if (g_code == 3)
		g_code = 131;
	else
		g_code = WEXITSTATUS(g_code);
}

int	ft_start_bin(t_bin *param, char **tokens, char **c_env, t_fds fds)
{
	param->pid = fork();
	signal(SIGINT, ft_child_handler);
	signal(SIGQUIT, ft_child_handler);
	if (param->pid < 0)
	{
		if (param->value)
			free(param->value);
		return (ft_print_error("Fork error", 1));
	}
	else if (!param->pid)
	{
		if (fds.in_fd != 0)
			dup2(fds.in_fd, 0);
		if (fds.out_fd != 1)
			dup2(fds.out_fd, 1);
		execve(param->value, tokens, c_env);
	}
	wait(&g_code);
	ft_check_code();
	if (param->value)
		free(param->value);
	return (1);
}

int	ft_set_value(t_bin *param, char **tokens)
{
	param->value = ft_strndup(tokens[0], ft_strlen(tokens[0]));
	if (lstat(param->value, &param->buf) < 0)
	{
		free(param->value);
		return (1);
	}
	return (0);
}

int	ft_check_exec(t_bin *param, char **tokens, char **c_env, t_fds fds)
{
	if (param->paths)
		ft_free_env(param->paths);
	if (!param->value)
		if (ft_set_value(param, tokens))
			return (0);
	if (!(param->buf.st_mode & S_IFREG))
	{
		if (param->value)
			free(param->value);
		return (0);
	}
	if (!(param->buf.st_mode & S_IXUSR))
	{
		if (param->value)
			free(param->value);
		write(2, "minishell: permission denied: ", 30);
		ft_putendl_fd(param->value, 2);
		g_code = 126;
		return (-1);
	}
	return (ft_start_bin(param, tokens, c_env, fds));
}
