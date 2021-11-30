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

int	ft_print_error(char *msg, int code)
{
	ft_putendl_fd(msg, 2);
	g_code = code;
	return (-1);
}

int	ft_is_start_str(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_start_bin(t_bin *param, char **tokens, char **c_env, int fd)
{
	param->pid = fork();
	signal(SIGINT, ft_child_handler);
	if (param->pid < 0)
	{
		if (param->value)
			free(param->value);
		return (ft_print_error("Fork error", 1));
	}
	else if (!param->pid)
	{
		if (fd != 1)
			dup2(fd, 1);
		execve(param->value, tokens, c_env);
	}
	wait(&param->pid);
	if (param->value)
		free(param->value);
	return (1);
}

int	ft_check_exec(t_bin *param, char **tokens, char **c_env, int fd)
{
	ft_free_env(param->paths);
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
	return (ft_start_bin(param, tokens, c_env, fd));
}
