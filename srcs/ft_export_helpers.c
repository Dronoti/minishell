/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:00:27 by timur             #+#    #+#             */
/*   Updated: 2021/11/26 12:00:30 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cascade_var(t_var *var)
{
	free(var->key);
	var->key = NULL;
	free(var->value);
	var->value = NULL;
	free(var);
	var = NULL;
}

void	update_var(char **existing_var_record, t_var *new_var)
{
	char	*tmp;
	char	*new_var_str;

	tmp = ft_strjoin(new_var->key, "=");
	if (!tmp)
		ft_errors("Malloc error", 1);
	new_var_str = ft_strjoin(tmp, new_var->value);
	if (!new_var_str)
		ft_errors("Malloc error", 1);
	free(tmp);
	tmp = NULL;
	tmp = *existing_var_record;
	*existing_var_record = new_var_str;
	free(tmp);
}

void	ft_extend_env(char ***env, t_var *new_var)
{
	char	**copy;
	int		i;
	char	**new_var_str;

	g_code = 0;
	i = 0;
	while ((*env)[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 2));
	if (!copy)
		ft_errors("Malloc error", 1);
	i = copy_env_vars(copy, *env);
	new_var_str = malloc(sizeof(char *));
	update_var(new_var_str, new_var);
	ft_free_env(*env);
	copy[i] = *new_var_str;
	copy[i + 1] = NULL;
	*env = copy;
}

void	setup_var(t_var *var, char *var_str)
{
	if (ft_strcmp(get_starting_from_symbol(var_str, '='), var_str) == 0)
	{
		var->key_len = ft_strlen(var_str);
		var->value_len = 0;
	}
	else if (get_starting_from_symbol(var_str, '=') - var_str + 1
		== ft_strlen(var_str))
	{
		var->key_len = ft_strlen(var_str) - 1;
		var->value_len = 0;
	}
	else
	{
		var->key_len = (int)(get_starting_from_symbol(var_str, '=') - var_str);
		var->value_len = (int)
			(var_str
				+ (ft_strlen(var_str) - 1)
				- get_starting_from_symbol(var_str, '='));
	}
	var->key = ft_strndup(var_str, var->key_len);
	if (!var->key)
		ft_errors("Malloc error", 1);
	var->value = ft_strndup(var_str + var->key_len + 1, var->value_len);
	if (!var->value)
		ft_errors("Malloc error", 1);
}

int	is_valid_var_key(char *key)
{
	int	i;

	if (key[0] >= '0' && key[0] <= '9')
		return (0);
	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] == '_')
			continue ;
		if (key[i] < '0' || (key[i] > '9' && key[i] < 'A'))
			return (0);
		if ((key[i] > 'Z' && key[i] < 'a') || key[i] > 'z')
			return (0);
		i++;
	}
	return (1);
}
