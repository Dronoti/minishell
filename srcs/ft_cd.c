/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:26:05 by timur             #+#    #+#             */
/*   Updated: 2021/11/16 20:26:10 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	traversing_resolve_dots(char **path_splitted)
{
	int	i;

	i = 0;
	while (path_splitted[i] != NULL)
	{
		if (ft_strcmp(path_splitted[i], ".") == 0)
		{
			free(path_splitted[i]);
			path_splitted[i] = NULL;
		}
		else if (ft_strcmp(path_splitted[i], "..") == 0)
		{
			ft_cd_nullify_preceding_pathname(path_splitted, i - 1);
			free(path_splitted[i]);
			path_splitted[i] = NULL;
		}
		i++;
	}
	return (i);
}

int	ft_cd(char **args, int fd, char ***env)
{
	char	**path_splitted;
	char	*path;
	int		len;

	(void) fd;
	path_splitted = get_path_splitted(args, *env);
	if (!path_splitted)
		return (-1);
	len = traversing_resolve_dots(path_splitted);
	path = construct_abs_path(path_splitted, len);
	if (chdir(path) != 0)
	{
		err_print_no_such_file_or_dir(args[1]);
		free(path);
		return (-1);
	}
	set_oldpwd_var(*env);
	set_pwd_var(env, path);
	free(path);
	return (1);
}

char	*construct_abs_path(char **path_splitted, int len)
{
	if (is_empty(path_splitted, len))
		return (construct_root_path(path_splitted));
	return (constract_non_root_path(path_splitted, len));
}

char	*get_path_raw(char *const *args, char *cwd, char **env)
{
	char	*path_raw;
	char	*home_var_value;

	if (args[1] == NULL)
	{
		home_var_value = ft_get_value_env("HOME", env);
		if (home_var_value == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		path_raw = ft_strndup(home_var_value, ft_strlen(home_var_value));
	}
	else if (args[1][0] == '/')
		path_raw = ft_strndup(args[1], ft_strlen(args[1]));
	else
		path_raw = ft_strjoin(cwd, args[1]);
	return (path_raw);
}

char	**get_path_splitted(char *const *args, char **env)
{
	char	*cwd_without_trail_slash;
	char	*cwd;
	char	*path_raw;
	char	**path_splitted;

	cwd_without_trail_slash = getcwd(NULL, 0);
	if (cwd_without_trail_slash == NULL)
		return (NULL);
	cwd = ft_strjoin(cwd_without_trail_slash, "/");
	free(cwd_without_trail_slash);
	if (cwd == NULL)
		return (NULL);
	path_raw = get_path_raw(args, cwd, env);
	free(cwd);
	if (!path_raw)
		return (NULL);
	path_splitted = ft_split(path_raw, '/');
	free(path_raw);
	if (!path_splitted)
		return (NULL);
	return (path_splitted);
}
