/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:50:59 by timur             #+#    #+#             */
/*   Updated: 2021/11/26 21:51:01 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_single_var_line(int fd, t_var *var, char *var_str)
{
	if (write(fd, "declare -x ", ft_strlen("declare -x ")) == -1)
		return (ft_write_error());
	if (write(fd, var->key, ft_strlen(var->key)) == -1)
		return (ft_write_error());
	if (*(var_str + ft_strlen(var->key)) == '=')
	{
		if (write(fd, "=\"", sizeof("\"")) == -1)
			return (ft_write_error());
		if (write(fd, var->value, sizeof(char) * ft_strlen(var->value)) == -1)
			return (ft_write_error());
		if (write(fd, "\"", sizeof("\"")) == -1)
			return (ft_write_error());
	}
	if (write(fd, "\n", sizeof("\n")) == -1)
		return (ft_write_error());
	return (1);
}
