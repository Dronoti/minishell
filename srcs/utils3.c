/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:02:48 by bkael             #+#    #+#             */
/*   Updated: 2021/11/22 20:03:02 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

t_p	ft_init_arg(char ***tokens, char ***c_env, char *cmd, char *prompt)
{
	t_p	new;

	new.save_in = dup(0);
	new.start = 0;
	new.end = 0;
	new.pid = -1;
	new.children = 0;
	new.fd1[0] = -1;
	new.fd1[1] = -1;
	new.fd2[0] = -1;
	new.fd2[1] = -1;
	new.last = 1;
	new.copy = NULL;
	new.tokens = tokens;
	new.c_env = c_env;
	new.cmd = cmd;
	new.prompt = prompt;
	return (new);
}

void	ft_free_exit(char ***tokens, char ***c_env, char *cmd, char *prompt)
{
	ft_free_tokens(*tokens);
	ft_free_env(*c_env);
	if (cmd)
		free(cmd);
	if (prompt)
		free(prompt);
	exit(g_code);
}

char	*ft_get_value_env(char *key, char **c_env)
{
	char	*value;
	int		i;

	value = NULL;
	i = -1;
	while (c_env[++i] && !value)
		if (ft_find_key(key, c_env[i]))
			value = ft_get_value(c_env[i]);
	return (value);
}
