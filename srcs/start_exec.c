/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:32:45 by bkael             #+#    #+#             */
/*   Updated: 2021/11/22 19:33:03 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_bins(char **tokens, char ***c_env, int fd)
{
	(void)tokens;
	(void)c_env;
	(void)fd;
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

int	ft_start_exec(char ***tokens, char ***c_env, char *cmd, char *prompt)
{
	int	fd;
	int	is_bin;
	int	is_builtins;

	fd = ft_check_redirect(tokens);
	if (fd < 0)
		return (1);
	is_bin = 0;
	is_builtins = ft_check_builtins(*tokens, c_env, fd);
	if (!is_builtins)
		is_bin = ft_check_bins(*tokens, c_env, fd);
	if (fd != 1)
		close(fd);
	if (!is_builtins && !is_bin)
	{
		write(2, "minishell: command not found: ", 30);
		ft_putendl_fd(cmd, 2);
		g_code = 127;
		return (1);
	}
	if (is_builtins == -2)
		ft_free_exit(tokens, c_env, cmd, prompt);
	if (is_builtins == -1 || is_bin == -1)
		return (1);
	return (0);
}
