/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftimothy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:28:23 by ftimothy          #+#    #+#             */
/*   Updated: 2020/11/22 18:30:33 by ftimothy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, int start, size_t len)
{
	int	result_len;
	char				*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		result_len = 0;
	else
		result_len = start + (int) len < ft_strlen(s) ? (int) len : ft_strlen(s) - start;
	if (!(p = malloc((result_len + 1) * sizeof(char))))
		return (0);
	ft_memmove(p, &s[start], result_len);
	p[result_len] = '\0';
	return (p);
}
