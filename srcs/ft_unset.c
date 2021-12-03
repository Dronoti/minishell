/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:59:00 by timur             #+#    #+#             */
/*   Updated: 2021/11/27 11:59:03 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, int fd, char ***c_env)
{
	int		i;
	char	**existing_var_record;

	(void)fd;
	if (args[1] == NULL)
		return (1);
	i = 1;
	while (args[i] != NULL)
	{
		existing_var_record = get_existing_var_record(*c_env, args[i]);
		if (existing_var_record == NULL)
		{
			i++;
			continue ;
		}
		unset_var(existing_var_record, c_env);
		i++;
	}
	return (1);
}

int	get_len(char **env)
{
	int		i;

	i = 0;
	while ((*env)[i])
		i++;
	return (i);
}

void	unset_var(char **existing_var_record, char ***env)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * get_len(*env));
	if (!copy)
		ft_errors("Malloc error", 1);
	i = 0;
	while (i < existing_var_record - (*env))
	{
		copy[i] = ft_strndup((*env)[i], ft_strlen((*env)[i]));
		if (!copy[i])
			ft_errors("Malloc error", 1);
		i++;
	}
	while ((*env)[i + 1])
	{
		copy[i] = ft_strndup((*env)[i + 1], ft_strlen((*env)[i + 1]));
		if (!copy[i])
			ft_errors("Malloc error", 1);
		i++;
	}
	copy[i] = NULL;
	ft_free_env(*env);
	*env = copy;
}
