/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:38:47 by bkael             #+#    #+#             */
/*   Updated: 2021/11/09 21:39:05 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_key(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_lennum(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		sing;

	sing = 1;
	len = ft_lennum(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		sing = -1;
		res[0] = '-';
	}
	if (n == 0)
		res[0] = '0';
	res[len] = '\0';
	len--;
	while (n)
	{
		res[len] = '0' + sing * (n % 10);
		n /= 10;
		len--;
	}
	return (res);
}

char	*ft_get_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str)
		str++;
	return (str);
}

void	ft_remove_char(char **token, int i, int len)
{
	char	*buf_start;
	char	*buf_end;

	buf_start = ft_strndup(*token, i);
	buf_end = ft_strndup(&(*token)[i + 1], len - i);
	free(*token);
	*token = ft_strjoin(buf_start, buf_end);
	free(buf_start);
	free(buf_end);
}
