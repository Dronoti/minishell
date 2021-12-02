/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_heredoc_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:56:33 by timur             #+#    #+#             */
/*   Updated: 2021/12/02 20:56:35 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_heredoc_replace_vars(char *cmd, char **c_env)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (cmd[i])
	{
		ft_check_var(&new, cmd, &i, c_env);
		if (cmd[i])
			i++;
	}
	free(cmd);
	return (new);
}

void	write_tmp_heredoc_file(char *heredoc)
{
	int		fd;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
}

int	is_it_quoted(char *raw_delimiter)
{
	int		i;

	i = 0;
	while (raw_delimiter[i])
	{
		if (raw_delimiter[i] == '\'' || raw_delimiter[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
