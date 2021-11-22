/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:58:59 by bkael             #+#    #+#             */
/*   Updated: 2021/11/22 18:59:22 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redir(char **tokens)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
		{
			if (!ft_strcmp(tokens[i + 1], ">") || !tokens[i + 1]
				|| !ft_strcmp(tokens[i + 1], ">>"))
			{
				write(2, "minishell: parse error near `", 29);
				if (tokens[i + 1])
					write(2, tokens[i + 1], ft_strlen(tokens[i + 1]));
				else
					write(2, "\\n", 2);
				ft_putendl_fd("'", 2);
				g_code = 1;
				return (-1);
			}
			count++;
		}
	}
	return (count);
}

char	**ft_delete_redir(char **tokens, int count_redir)
{
	int		i;
	int		count_tok;
	char	**copy;

	count_tok = 0;
	while (tokens[count_tok])
		count_tok++;
	copy = (char **)malloc(sizeof(char *) * (count_tok - count_redir * 2 + 1));
	i = -1;
	count_tok = 0;
	while (tokens[++i] && copy)
	{
		if (!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
			i++;
		else
		{
			copy[count_tok] = ft_strndup(tokens[i], ft_strlen(tokens[i]));
			if (!copy[count_tok++])
				copy = ft_free_tokens(copy);
		}
	}
	if (copy)
		copy[count_tok] = NULL;
	ft_free_tokens(tokens);
	return (copy);
}

char	**ft_init_fd(int *fd, char **tokens, int count_redir)
{
	int	i;
	int	r;

	i = -1;
	r = count_redir;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], ">"))
			*fd = open(tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strcmp(tokens[i], ">>"))
			*fd = open(tokens[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		if ((!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
			&& *fd < 0)
		{
			write(2, "minishell: invalid redirect: ", 29);
			ft_putendl_fd(tokens[i + 1], 2);
			return (tokens);
		}
		if ((!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>")))
			if (--r)
				close(*fd);
	}
	return (ft_delete_redir(tokens, count_redir));
}

int	ft_check_redirect(char ***tokens)
{
	int	fd;
	int	count_redir;

	count_redir = ft_count_redir(*tokens);
	fd = 1;
	if (count_redir == -1)
		return (-1);
	if (count_redir)
		*tokens = ft_init_fd(&fd, *tokens, count_redir);
	if (!*tokens)
	{
		ft_putendl_fd("Malloc error", 2);
		g_code = 1;
		return (-1);
	}
	return (fd);
}
