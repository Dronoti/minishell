/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:00:14 by timur             #+#    #+#             */
/*   Updated: 2021/11/26 12:00:16 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, int fd, char ***c_env)
{
	int	i;
	int	exit;

	exit = 1;
	if (args[1] == NULL)
		return (handle_no_params(fd, *c_env));
	i = -1;
	while (args[++i] != NULL)
	{
		if (ft_strcmp(get_starting_from_symbol(args[i], '='), "\0") == 0)
		{
			if (!is_valid_var_key(args[i]))
			{
				write(2, "minishell: export: `", 20);
				write(2, args[i], ft_strlen(args[i]));
				write(2, "': not a valid identifier\n", 26);
				g_code = 1;
				exit = -1;
			}
			continue ;
		}
		if (handle_str_with_equals_sign(args[i], c_env))
			exit = -1;
	}
	return (exit);
}

int	handle_no_params(int fd, char **c_env)
{
	int		i;
	t_var	*var;

	i = 0;
	while (c_env[i])
	{
		var = malloc(sizeof(t_var));
		if (!var)
			ft_errors("Malloc error", 1);
		setup_var(var, c_env[i]);
		if (write_single_var_line(fd, var, c_env[i]) == -1)
			return (-1);
		free_cascade_var(var);
		i++;
	}
	return (1);
}

char	*get_starting_from_symbol(char *s, char c)
{
	if ((char *)ft_memchr(s, c, ft_strlen(s)) == 0)
		return ((char *)ft_memchr(s, '\0', ft_strlen(s) + 1));
	return ((char *)ft_memchr(s, c, ft_strlen(s)));
}

int	handle_str_with_equals_sign(char *str, char ***c_env)
{
	t_var	*var;
	char	**existing_var_record;

	var = malloc(sizeof(t_var));
	if (!var)
		ft_errors("Malloc error", 1);
	setup_var(var, str);
	if (!is_valid_var_key(var->key))
	{
		write(2, "minishell: export: `", ft_strlen("minishell: export: `"));
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n",
			ft_strlen("': not a valid identifier\n"));
		free_cascade_var(var);
		g_code = 1;
		return (1);
	}
	existing_var_record = get_existing_var_record(*c_env, var->key);
	if (existing_var_record)
		update_var(existing_var_record, var);
	else
		ft_extend_env(c_env, var);
	free_cascade_var(var);
	return (0);
}

char	**get_existing_var_record(char **env, char *var_key)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp = ft_substr(env[i], 0, ft_strlen(var_key));
		if (ft_strcmp(tmp, var_key) == 0)
		{
			if (env[i][ft_strlen(var_key)] == '=')
			{
				free(tmp);
				return (&env[i]);
			}
		}
		free(tmp);
		i++;
	}
	return (NULL);
}
