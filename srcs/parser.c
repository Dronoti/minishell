/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:30:46 by bkael             #+#    #+#             */
/*   Updated: 2021/11/21 14:31:08 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char **newcmd, char *cmd, int *i, int *inside)
{
	if (cmd[*i] == '"' && !*inside)
		*inside = 1;
	else if (cmd[*i] == '"' && *inside)
		*inside = 0;
	if (cmd[*i] == '\'' && !*inside)
	{
		*newcmd = ft_join_char(*newcmd, cmd[*i]);
		(*i)++;
		while (cmd[*i] != '\'')
		{
			*newcmd = ft_join_char(*newcmd, cmd[*i]);
			(*i)++;
		}
	}
}

void	ft_check_var(char **newcmd, char *cmd, int *i, char **c_env)
{
	char	*code;

	code = NULL;
	if (cmd[*i] == '$' && cmd[*i + 1] == '?')
	{
		(*i)++;
		code = ft_itoa(g_code);
		*newcmd = ft_join_env(*newcmd, code);
		free(code);
	}
	else if (cmd[*i] == '$'
		&& (cmd[*i + 1] && cmd[*i + 1] != '\'' && cmd[*i + 1] != '}'
			&& cmd[*i + 1] != '"' && cmd[*i + 1] != '/'
			&& !ft_isspace(cmd[*i + 1])))
		*newcmd = ft_join_env(*newcmd, ft_find_env(cmd, c_env, i));
	else if (cmd[*i] == '~'
		&& (*i == 0 || (*i != 0 && cmd[*i - 1] == '"')
			|| (*i != 0 && cmd[*i - 1] == '\'')
			|| (*i != 0 && ft_isspace(cmd[*i - 1]))))
		*newcmd = ft_join_env(*newcmd, ft_find_env(cmd, c_env, i));
	else if (cmd[*i])
		*newcmd = ft_join_char(*newcmd, cmd[*i]);
}

char	*ft_replace_env(char *cmd, char **c_env)
{
	char	*new;
	int		inside;
	int		i;

	i = 0;
	inside = 0;
	new = NULL;
	while (cmd[i])
	{
		ft_check_quotes(&new, cmd, &i, &inside);
		ft_check_var(&new, cmd, &i, c_env);
		if (cmd[i])
			i++;
	}
	free(cmd);
	return (new);
}

void	print_error_and_set_g_code(char *msg, int g_code_value)
{
	ft_putendl_fd(msg, 2);
	g_code = g_code_value;
}

void	ft_parser(char **cmd, char ***c_env, char *prompt)
{
	char	**tokens;

	if (ft_isvalid_quotes(*cmd) || ft_isvalid_pipes_braces(*cmd))
		return (print_error_and_set_g_code("Error: Invalid command line", 1));
	*cmd = ft_replace_env(*cmd, *c_env);
	if (!*cmd)
		return (print_error_and_set_g_code("Malloc error", 1));
	tokens = ft_create_tokens(*cmd);
	if (!tokens)
		return (print_error_and_set_g_code("Malloc error", 1));
	if (!ft_check_heredoc(tokens))
		return (print_error_and_set_g_code("Malloc error", 1));
	if (!ft_check_pipe(&tokens, c_env, *cmd, prompt))
		g_code = 0;
	ft_free_tokens(tokens);
}
