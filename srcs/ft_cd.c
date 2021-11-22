/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:26:05 by timur             #+#    #+#             */
/*   Updated: 2021/11/16 20:26:10 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_path_splitted(char *const *args);

int	ft_cd(char **args, int *fd) {
	char **path_splitted;
	char *path;

	(void) fd;
	path_splitted = get_path_splitted(args);
	if (!path_splitted)
		return (-1);

	int i;
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
			int j;
			j = i - 1;
			while (j >= 0) {
				if (path_splitted[j] != NULL && ft_strcmp(path_splitted[j], "..") != 0)
				{
					free(path_splitted[j]);
					path_splitted[j] = NULL;
					break;
				}
				j--;
			}
			free(path_splitted[i]);
			path_splitted[i] = NULL;
		}
		i++;
	}

	char *tmp_path;
	int len;
	len = i;
	i = 0;
	path = ft_strndup("/", ft_strlen("/"));
	while (len > 0)
	{
		if (path_splitted[i] != NULL)
		{
			tmp_path = path;
			path = ft_strjoin(path, path_splitted[i]);
			free(path_splitted[i]);
			path_splitted[i] = NULL;
			free(tmp_path);
			tmp_path = path;
			path = ft_strjoin(path, "/");
			free(tmp_path);
		}
		i++;
		len--;
	}
	free(path_splitted);
	if (chdir(path) != 0)
	{
		free(path);
		return (-1);
	}
	free(path);
	return (1);
}

char *get_path_raw(char *const *args, char *cwd)
{
	char *path_raw;

	if (args[1] == NULL)
		path_raw = ft_strndup(getenv("HOME"), ft_strlen(getenv("HOME")));
	else if (args[1][0] == '/')
		path_raw = ft_strndup(args[1], ft_strlen(args[1]));
	else
		path_raw = ft_strjoin(cwd, args[1]);
	return (path_raw);
}

char **get_path_splitted(char *const *args)
{
	char *cwd_without_trail_slash;
	char *cwd;
	char *path_raw;
	char **path_splitted;

	cwd_without_trail_slash = getcwd(NULL, 0);
	if (cwd_without_trail_slash == NULL)
		return (NULL);
	cwd = ft_strjoin(cwd_without_trail_slash, "/");
	free(cwd_without_trail_slash);
	if (cwd == NULL)
		return (NULL);
	path_raw = get_path_raw(args, cwd);
	free(cwd);
	if (!path_raw)
		return (NULL);
	path_splitted = ft_split(path_raw, '/');
	free(path_raw);
	if (!path_splitted)
		return (NULL);
	return (path_splitted);
}
