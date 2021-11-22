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

int	ft_pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putendl_fd("Malloc error", 2);
		g_code = 1;
		return (-1);
	}
	if (write(fd, path, sizeof(char) * ft_strlen(path)) == -1
		|| write(fd, "\n", sizeof(char)) == -1)
	{
		free(path);
		return (ft_write_error());
	}
	free(path);
	return (1);
}
