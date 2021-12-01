/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:07:02 by timur             #+#    #+#             */
/*   Updated: 2021/12/01 20:07:04 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append(char *dst, char *src)
{
	char	*tmp;

	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	return (dst);
}

char	*get_heredoc(char *input, char *heredoc)
{
	if (heredoc == NULL)
		heredoc = ft_strndup(input, ft_strlen(input));
	else
		heredoc = ft_append(heredoc, input);
	if (!heredoc)
		return (NULL);
	heredoc = ft_append(heredoc, "\n");
	if (!heredoc)
		return (NULL);
	return (heredoc);
}

void	make_free(char **var)
{
	free(*var);
	*var = NULL;
}

int	read_heredoc(char *delimiter)
{
	char	*input;
	char	*heredoc;
	int		fd;

	heredoc = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			return (1);
		if (!ft_strcmp(delimiter, input))
		{
			make_free(&input);
			break ;
		}
		heredoc = get_heredoc(input, heredoc);
		make_free(&input);
		if (!heredoc)
			return (0);
	}
	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
	free(heredoc);
	return (1);
}

int	ft_check_heredoc(char **tokens)
{
	int		i;
	char	*delimiter;

	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], "<<"))
		{
			delimiter = tokens[i + 1];
			if (read_heredoc(delimiter) == 0)
				return (0);
		}
	}
	return (1);
}
