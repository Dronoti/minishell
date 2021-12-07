/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 08:22:02 by bkael             #+#    #+#             */
/*   Updated: 2021/12/07 08:22:19 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

static unsigned char	get_src_value(const void *src, size_t i)
{
	return (*(unsigned char *)(src + i));
}

void	*ft_memmove(void *dst, const void *src, size_t len)
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
