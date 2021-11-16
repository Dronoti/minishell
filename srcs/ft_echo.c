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
	char	bl;

	bl = '\n';
	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
		i++;
	while (args[i] != NULL)
	{
		write(fd[0], args[i], ft_strlen(args[i]) * sizeof(char));
		if (args[i + 1] != NULL)
			write(fd[0], " ", sizeof(char));
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		write(fd[0], &bl, sizeof(char));
	return (1);
}
