/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:54:33 by bkael             #+#    #+#             */
/*   Updated: 2021/11/09 14:54:56 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_token(char *cmd)
{
	int		i;
	char	c;

	i = 0;
	while (!ft_isspace(cmd[i]) && cmd[i] && !ft_isspec_char(&cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
		{
			c = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
		}
		if (cmd[i])
			i++;
	}
	if (i == 0)
		return (ft_isspec_char(cmd));
	return (i);
}

int	ft_count_tokens(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		while (ft_isspace(cmd[i]))
			i++;
		if (cmd[i])
			count++;
		i += ft_len_token(&cmd[i]);
	}
	return (count);
}

char	**ft_free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = NULL;
	}
	return (NULL);
}

void	ft_delete_quotes(char **token, int len)
{
	int		i;
	char	c;

	if (!token || !*token)
		return ;
	i = 0;
	while ((*token)[i])
	{
		if ((*token)[i] == '"' || (*token)[i] == '\'')
		{
			c = (*token)[i];
			ft_remove_char(token, i, len);
			while ((*token)[i] && (*token)[i] != c)
				i++;
			if ((*token)[i] == c)
				ft_remove_char(token, i, len);
		}
		if ((*token)[i] && (*token)[i] != '"' && (*token)[i] != '\'')
			i++;
	}
}

char	**ft_create_tokens(char *cmd)
{
	char	**tokens;
	int		count;
	int		i;
	int		j;
	int		len;

	count = ft_count_tokens(cmd);
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	j = -1;
	i = 0;
	while (++j < count)
	{
		while (ft_isspace(cmd[i]))
			i++;
		len = ft_len_token(&cmd[i]);
		tokens[j] = ft_strndup(&cmd[i], len);
		ft_delete_quotes(&tokens[j], len);
		if (!tokens[j])
			return (ft_free_tokens(tokens));
		i += len;
	}
	tokens[j] = NULL;
	return (tokens);
}
