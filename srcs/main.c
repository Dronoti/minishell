/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 08:39:32 by bkael             #+#    #+#             */
/*   Updated: 2021/11/21 15:59:50 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_prompt(char **c_env)
{
	char	*path;
	char	*prompt;
	int		i;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_free_env(c_env);
		ft_errors("Malloc error", 1);
	}
	i = ft_strlen(path);
	while (path[i - 1] != '/' && i != 0)
		i--;
	if (path[i])
		prompt = ft_join_shell("minishell ", &path[i]);
	else
		prompt = ft_join_shell("minishell ", "/");
	free(path);
	if (!prompt)
	{
		ft_free_env(c_env);
		ft_errors("Malloc error", 1);
	}
	return (prompt);
}

void	ft_free_all(char *prompt, char **c_env, char *cmd)
{
	if (prompt)
		free(prompt);
	if (cmd)
		free(cmd);
	ft_free_env(c_env);
	rl_clear_history();
}

int	ft_exist_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] > 32 && cmd[i] < 127)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	*prompt;
	char	**c_env;

	(void)argv;
	if (argc != 1)
		ft_errors("Error: Too many arguments", 1);
	c_env = ft_create_env(env);
	while (1)
	{
		ft_init_signals();
		prompt = ft_create_prompt(c_env);
		cmd = readline(prompt);
		if (!cmd)
			break ;
		if (ft_exist_cmd(cmd))
		{
			add_history(cmd);
			ft_parser(&cmd, &c_env, prompt);
		}
		if (cmd)
			free(cmd);
		free(prompt);
	}
	ft_free_all(prompt, c_env, NULL);
	return (0);
}
