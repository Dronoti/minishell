/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:25:05 by bkael             #+#    #+#             */
/*   Updated: 2021/11/02 11:25:23 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_errors(char *msg, int code)
{
	ft_putendl_fd(msg, 2);
	exit(code);
}

int	ft_isvalid_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			if (!cmd[i])
				return (1);
		}
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
				i++;
			if (!cmd[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_first_ispipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '|')
		return (1);
	else
		return (0);
}

int	ft_isvalid_pipes_braces(char *cmd)
{
	int	i;

	if (ft_first_ispipe(cmd))
		return (1);
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '|')
		{
			i++;
			if (!ft_exist_cmd(&cmd[i]))
				return (1);
		}
		if (cmd[i] == '$' && cmd[i + 1] == '{')
		{
			i += 2;
			if (!ft_isvalid_key(cmd[i]))
				return (1);
			while (cmd[i] && cmd[i] != '}')
				i++;
			if (cmd[i] != '}')
				return (1);
		}
	}
	return (0);
}

int	ft_print_error(char *msg, int code)
{
	ft_putendl_fd(msg, 2);
	g_code = code;
	return (-1);
}
