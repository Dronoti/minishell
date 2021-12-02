/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:32:04 by bkael             #+#    #+#             */
/*   Updated: 2021/11/09 12:32:24 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

char	*ft_strndup(char *s1, int n)
{
	char	*dup;
	int		i;
	int		len;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	if (n < len)
		len = n;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isspec_char(char *str)
{
	if (str[0] == '|' || str[0] == '>' || str[0] == '<')
	{
		if ((str[0] == '>' && str[1] == '>')
			|| (str[0] == '<' && str[1] == '<'))
			return (2);
		return (1);
	}
	return (0);
}
