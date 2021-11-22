/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftimothy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:32:34 by ftimothy          #+#    #+#             */
/*   Updated: 2020/11/22 18:32:39 by ftimothy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	get_words_count(char const *s, char c)
{
	unsigned long long	word_counter;
	unsigned long long	i;

	word_counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word_counter++;
		i++;
	}
	return (word_counter);
}

static char					**free_up(unsigned long long i, char **result)
{
	while (i != 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (0);
}

static char					*get_word_end(char *s, char c)
{
	if ((char *)ft_memchr(s, c, ft_strlen(s)) == 0)
		return ((char *)ft_memchr(s, '\0', ft_strlen(s) + 1));
	return ((char *)ft_memchr(s, c, ft_strlen(s)));
}

char						**ft_split(char *s, char c)
{
	unsigned long long	word_counter;
	unsigned long long	i;
	char				**result;

	if (!s)
		return (0);
	word_counter = get_words_count(s, c);
	if (!(result = malloc((word_counter + 1) * sizeof(char *))))
		return (0);
	i = 0;
	while (i < word_counter)
	{
		while (*s == c)
			s++;
		if (!(result[i] = malloc((get_word_end(s, c) - s + 1) * sizeof(char))))
			return (free_up(i, result));
		ft_memmove(result[i], s, get_word_end(s, c) - s);
		result[i][get_word_end(s, c) - s] = '\0';
		s = ft_memchr(s, c, ft_strlen(s));
		s++;
		i++;
	}
	result[word_counter] = 0;
	return (result);
}
