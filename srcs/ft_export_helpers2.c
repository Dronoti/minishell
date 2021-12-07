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

char	*ft_substr(char *s, int start, size_t len)
{
	int		result_len;
	char	*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		result_len = 0;
	else if ((int) len < ft_strlen(s))
		result_len = start + (int) len;
	else
		result_len = start + ft_strlen(s) - start;
	p = malloc((result_len + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_memmove(p, &s[start], result_len);
	p[result_len] = '\0';
	return (p);
}
