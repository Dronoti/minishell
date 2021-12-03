/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:19:00 by bkael             #+#    #+#             */
/*   Updated: 2021/11/03 17:19:34 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **c_env)
{
	int	i;

	i = 0;
	if (c_env)
	{
		while (c_env[i])
		{
			free(c_env[i]);
			i++;
		}
		free(c_env);
		c_env = NULL;
	}
}

char	**ft_create_env(char **env)
{
	char	**copy;
	int		i;

	g_code = 0;
	i = 0;
	while (env[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		ft_errors("Malloc error", 1);
	i = copy_env_vars(copy, env);
	copy[i] = NULL;
	return (copy);
}

int	copy_env_vars(char **dst, char *const *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strndup(src[i], ft_strlen(src[i]));
		if (!dst[i])
		{
			ft_free_env(dst);
			ft_errors("Malloc error", 1);
		}
		i++;
	}
	return (i);
}

int	ft_find_key(char *key, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!key)
		return (0);
	while (key[j] || (str[i] && str[i] != '='))
	{
		if (j == 0 && key[j] == '{')
			j++;
		if (key[j] != str[i])
			return (0);
		i++;
		j++;
		if (key[j] == '}' && str[i] == '=')
			return (1);
	}
	return (1);
}

char	*ft_find_env(char *cmd, char **c_env, int *i)
{
	char	*value;
	char	*key;
	int		j;

	key = NULL;
	value = NULL;
	if (cmd[*i] == '~')
		key = "HOME";
	else
	{
		while (ft_isvalid_key(cmd[*i + 1])
			|| (cmd[*i + 1] == '{' && cmd[*i] == '$')
			|| (cmd[*i + 1] == '}' && !ft_isvalid_key(cmd[*i + 2])))
		{
			(*i)++;
			key = ft_join_char(key, cmd[*i]);
		}
	}
	j = -1;
	while (c_env[++j])
		if (ft_find_key(key, c_env[j]))
			value = ft_get_value(c_env[j]);
	if (cmd[*i] != '~')
		free(key);
	return (value);
}
