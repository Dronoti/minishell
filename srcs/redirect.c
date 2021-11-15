/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:58:59 by bkael             #+#    #+#             */
/*   Updated: 2021/11/11 18:59:22 by bkael            ###   ########.fr       */
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
				|| !ft_strcmp(tokens[i + 1], ">>") || i == 0)
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

void	ft_close_fd(int *fd)
{
	int	i;

	if (fd)
	{
		i = 0;
		while (fd[i] > 1)
		{
			close(fd[i]);
			i++;
		}
		free(fd);
		fd = NULL;
	}
}

char	**ft_delete_redir(char **tokens, int count_redir)
{
	int		i;
	int		count_tokens;
	char	**copy;

	count_tokens = 0;
	while (tokens[count_tokens])
		count_tokens++;
	count_tokens -= count_redir * 2;
	copy = (char **)malloc(sizeof(char *) * (count_tokens + 1));
	i = 0;
	count_tokens = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
			i++;
		else
			copy[count_tokens++] = ft_strndup(tokens[i], ft_strlen(tokens[i]));
		i++;
	}
	copy[count_tokens] = NULL;
	ft_free_tokens(tokens);
	return (copy);
}

char	**ft_init_fd(int **fd, char **tokens, int count_redir)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		if (!ft_strcmp(tokens[i], ">"))
			(*fd)[j++] = open(tokens[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strcmp(tokens[i], ">>"))
			(*fd)[j++] = open(tokens[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
		if ((!ft_strcmp(tokens[i], ">") || !ft_strcmp(tokens[i], ">>"))
			&& (*fd)[j - 1] < 0)
		{
			write(2, "minishell: invalid redirect: ", 29);
			ft_putendl_fd(tokens[i + 1], 2);
			ft_close_fd(*fd);
			*fd = NULL;
			return (tokens);
		}
	}
	(*fd)[j] = 0;
	return (ft_delete_redir(tokens, count_redir));
}

int	*ft_check_redirect(char ***tokens)
{
	int	*fd;
	int	count_redir;

	count_redir = ft_count_redir(*tokens);
	if (count_redir == -1)
		return (NULL);
	if (count_redir)
		fd = (int *)malloc(sizeof(int) * (count_redir + 1));
	else
		fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
	{
		ft_putendl_fd("Malloc error", 2);
		g_code = 1;
		return (NULL);
	}
	if (count_redir)
		*tokens = ft_init_fd(&fd, *tokens, count_redir);
	else
	{
		fd[0] = 1;
		fd[1] = 0;
	}
	return (fd);
}
