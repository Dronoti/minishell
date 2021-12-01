/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:32:45 by bkael             #+#    #+#             */
/*   Updated: 2021/11/30 19:33:03 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_bins(char **tokens, char ***c_env, t_fds fds)
{
	int		i;
	t_bin	param;

	param.value = ft_get_value_env("PATH", *c_env);
	if (!param.value)
		return (0);
	param.paths = ft_split(param.value, ':');
	if (!param.paths)
		return (ft_print_error("Malloc error", 1));
	i = -1;
	while (param.paths[++i])
	{
		if (ft_is_start_str(param.paths[i], tokens[0]))
			param.value = ft_strndup(tokens[0], ft_strlen(tokens[0]));
		else
			param.value = ft_join_path(&param.paths[i], tokens[0]);
		if (lstat(param.value, &param.buf) < 0)
			free(param.value);
		else
			return (ft_check_exec(&param, tokens, *c_env, fds));
	}
	ft_free_env(param.paths);
	return (0);
}

int	ft_check_builtins(char **tokens, char ***c_env, int fd)
{
	(void)c_env;
	if (!ft_strcmp(tokens[0], "echo"))
		return (ft_echo(tokens, fd));
	if (!ft_strcmp(tokens[0], "pwd"))
		return (ft_pwd(fd));
	else if (!ft_strcmp(tokens[0], "cd"))
		return (ft_cd(tokens, fd, c_env));
	else if (!ft_strcmp(tokens[0], "env"))
		return (ft_env(tokens, fd, *c_env));
	else if (!ft_strcmp(tokens[0], "export"))
		return (ft_export(tokens, fd, c_env));
	else if (!ft_strcmp(tokens[0], "unset"))
		return (ft_unset(tokens, fd, c_env));
	else if (!ft_strcmp(tokens[0], "exit"))
		return (ft_exit(tokens));
	return (0);
}

t_fds	select_fds(char ***tokens)
{
	t_fds	fds;

	fds.in_fd = ft_check_redirect_input(tokens);
	fds.out_fd = ft_check_redirect(tokens);
	return (fds);
}

void	close_not_needed_fds(t_fds fds)
{
	if (fds.in_fd != 0)
		close(fds.in_fd);
	if (fds.out_fd != 1)
		close(fds.out_fd);
}

int	ft_start_exec(char ***tokens, char ***c_env, char *cmd, char *prompt)
{
	t_fds	fds;
	int		is_bin;
	int		is_builtins;

	fds = select_fds(tokens);
	if (fds.in_fd < 0 || fds.out_fd < 0)
		return (1);
	is_bin = 0;
	is_builtins = ft_check_builtins(*tokens, c_env, fds.out_fd);
	if (!is_builtins)
		is_bin = ft_check_bins(*tokens, c_env, fds);
	close_not_needed_fds(fds);
	if (!is_builtins && !is_bin)
	{
		write(2, "minishell: command not found: ", 30);
		ft_putendl_fd(cmd, 2);
		g_code = 127;
		return (1);
	}
	if (is_builtins == -2)
		ft_free_exit(tokens, c_env, cmd, prompt);
	if (is_builtins == -1 || is_bin)
		return (1);
	return (0);
}
