/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:46:15 by bkael             #+#    #+#             */
/*   Updated: 2021/11/06 17:46:34 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_shell(char *s1, char *s2)
{
	char	*join;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 4);
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		join[i++] = *s2;
		s2++;
	}
	join[i++] = ' ';
	join[i++] = '$';
	join[i++] = ' ';
	join[i] = '\0';
	return (join);
}

char	*ft_join_char(char *s, char c)
{
	char	*join;
	int		i;

	if (!c)
		return (NULL);
	i = 0;
	if (!s)
	{
		s = (char *)malloc(sizeof(char));
		if (!s)
			return (NULL);
		s[i] = '\0';
	}
	join = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!join)
		return (NULL);
	while (s[i])
	{
		join[i] = s[i];
		i++;
	}
	join[i++] = c;
	join[i] = '\0';
	free(s);
	return (join);
}

char	*ft_join_env(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i++] = s2[j];
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	while (*s1)
	{
		join[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		join[i] = *s2;
		s2++;
		i++;
	}
	join[i] = '\0';
	return (join);
}
