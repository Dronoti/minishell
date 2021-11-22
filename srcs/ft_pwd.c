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

int	ft_pwd(char **args, int *fd)
{
	char	*path;
	int		i;

	(void)args;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (-1);
	i = 0;
	while (fd[i])
	{
		if (write(fd[i], path, ft_strlen(path)) == -1
			|| write(fd[i], "\n", sizeof(char)) == -1)
		{
			free(path);
			return (-1);
		}
		i++;
	}
	free(path);
	return (1);
}
