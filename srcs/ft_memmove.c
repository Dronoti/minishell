/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftimothy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 23:55:52 by ftimothy          #+#    #+#             */
/*   Updated: 2020/11/09 23:13:43 by ftimothy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	get_src_value(const void *src, size_t i)
{
	return (*(unsigned char *)(src + i));
}

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((dst == 0 && src == 0))
		return (dst);
	if (dst > src)
	{
		while (len != 0)
		{
			*(unsigned char *)(dst + len - 1) = get_src_value(src, len - 1);
			len--;
		}
		return (dst);
	}
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	return (dst);
}
