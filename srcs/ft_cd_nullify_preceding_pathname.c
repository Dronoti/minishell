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
