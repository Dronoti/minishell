/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 02:50:40 by timur             #+#    #+#             */
/*   Updated: 2021/11/24 02:50:44 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, int fd, char **c_env)
{
	int	i;

	if (args[1] != NULL)
	{
		ft_putendl_fd("env: Arguments are not allowed", fd);
		g_code = 127;
		return (-1);
	}
	i = 0;
	while (c_env[i] != NULL)
	{
		ft_putendl_fd(c_env[i], fd);
		i++;
	}
	return (1);
}
