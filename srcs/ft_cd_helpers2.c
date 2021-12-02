/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helpers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 00:53:17 by timur             #+#    #+#             */
/*   Updated: 2021/12/03 00:53:19 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char **path_splitted, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		if (path_splitted[i] != NULL)
			return (0);
		i++;
		len--;
	}
	return (1);
}

char	*constract_non_root_path(char **path_splitted, int len)
{
	int		i;
	char	*path;
	char	*tmp_path;

	i = 0;
	path = malloc(sizeof(char));
	*path = '\0';
	while (len > 0)
	{
		if (path_splitted[i] != NULL)
		{
			tmp_path = path;
			path = ft_strjoin(path, "/");
			make_free(&tmp_path);
			tmp_path = path;
			path = ft_strjoin(path, path_splitted[i]);
			make_free(&path_splitted[i]);
			path_splitted[i] = NULL;
			make_free(&tmp_path);
		}
		i++;
		len--;
	}
	free(path_splitted);
	return (path);
}

char	*construct_root_path(char **path_splitted)
{
	char	*tmp_path;
	char	*path;

	path = malloc(sizeof(char));
	*path = '\0';
	tmp_path = path;
	path = ft_strjoin(path, "/");
	free(tmp_path);
	free(path_splitted);
	return (path);
}
