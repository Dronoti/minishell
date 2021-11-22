/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:24:50 by timur             #+#    #+#             */
/*   Updated: 2021/11/16 13:24:55 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_error(void)
{
	ft_putendl_fd("Write error", 2);
	g_code = 1;
	return (-1);
}

int	ft_echo(char **args, int fd)
{
	int		i;

	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
		i++;
	while (args[i] != NULL)
	{
		if (write(fd, args[i], ft_strlen(args[i]) * sizeof(char)) == -1)
			return (ft_write_error());
		if (args[i + 1] != NULL)
			if (write(fd, " ", sizeof(char)) == -1)
				return (ft_write_error());
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		if (write(fd, "\n", sizeof(char)) == -1)
			return (ft_write_error());
	return (1);
}
