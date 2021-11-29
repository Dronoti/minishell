/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_nullify_preceding_pathname.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:26:05 by timur             #+#    #+#             */
/*   Updated: 2021/11/16 20:26:10 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_nullify_preceding_pathname(char **path_splitted, int j)
{
	while (j >= 0)
	{
		if (path_splitted[j] != NULL
			&& ft_strcmp(path_splitted[j], "..") != 0)
		{
			free(path_splitted[j]);
			path_splitted[j] = NULL;
			break ;
		}
		j--;
	}
}

void	err_print_no_such_file_or_dir(char *arg1)
{
	char	*arg;

	if (arg1 == NULL)
		arg = getenv("HOME");
	else
		arg = arg1;
	write(2, "minishell: cd: ", ft_strlen("minishell: cd: "));
	write(2, arg, ft_strlen(arg));
	write(2, ": No such file or directory\n",
		ft_strlen(": No such file or directory\n"));
	g_code = 1;
}

void	set_pwd_var(char **const *env, char *path)
{
	t_var	*var;
	char	*tmp;

	var = malloc(sizeof(t_var));
	if (!var)
		ft_errors("Malloc error", 1);
	if (get_existing_var_record(*env, "PWD") != NULL)
	{
		tmp = ft_strjoin("PWD=", path);
		setup_var(var, tmp);
		update_var(get_existing_var_record(*env, "PWD"), var);
		free(tmp);
	}
	free(var);
	var = NULL;
}

void	set_oldpwd_var(char **env)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		ft_errors("Malloc error", 1);
	if (get_existing_var_record(env, "OLDPWD") != NULL)
	{
		setup_var(var, *get_existing_var_record(env, "PWD"));
		free(var->key);
		var->key = NULL;
		var->key = ft_strndup("OLDPWD", ft_strlen("OLDPWD"));
		if (!var->key)
			ft_errors("Malloc error", 1);
		var->key_len = ft_strlen(var->key);
		update_var(get_existing_var_record(env, "OLDPWD"), var);
	}
	free(var);
	var = NULL;
}
