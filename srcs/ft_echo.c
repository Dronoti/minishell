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

int	ft_echo(char **args, int *fd)
{
	int		i;
	int		j;

	i = 0;
	while (fd[i])
	{
		j = 1;
		if (ft_strcmp(args[1], "-n") == 0)
			j++;
		while (args[j] != NULL)
		{
			if (write(fd[0], args[j], ft_strlen(args[j]) * sizeof(char)) == -1)
				return (-1);
			if (args[j + 1] != NULL)
				if (write(fd[0], " ", sizeof(char)) == -1)
					return (-1);
			j++;
		}
		if (ft_strcmp(args[1], "-n") != 0)
			if (write(fd[0], "\n", sizeof(char)) == -1)
				return (-1);
		i++;
	}
	return (1);
}
