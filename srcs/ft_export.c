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

char	*get_str_from_symbol(char *s, char c);
void	handle_str_with_equals_sign(char **str, char ***c_env);
char	**get_existing_var_record(char **env, char *var_key);

int	ft_export(char **args, int fd, char ***c_env)
{
	int	i;

	(void)fd;
	if (args[1] == NULL)
	{
		printf("Print all declare x-s");
		return (1);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strcmp(get_str_from_symbol(args[i], '='), "\0") == 0)
			continue ;
		handle_str_with_equals_sign(&(args[i]), c_env);
		i++;
	}
	return (1);
}

char	*get_str_from_symbol(char *s, char c)
{
	if ((char *)ft_memchr(s, c, ft_strlen(s)) == 0)
		return ((char *)ft_memchr(s, '\0', ft_strlen(s) + 1));
	return ((char *)ft_memchr(s, c, ft_strlen(s)));
}

void	handle_str_with_equals_sign(char **str, char ***c_env)
{
	t_var	*var;
	char	**existing_var_record;

	var = malloc(sizeof(t_var));
	if (!var)
		ft_errors("Malloc error", 1);
	setup_var(var, str);
	if (!is_valid_var_key(var->key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", *str);
		free(var->key);
		free(var->value);
		free(var);
		return ;
	}
	existing_var_record = get_existing_var_record(*c_env, var->key);
	if (existing_var_record)
		update_var(existing_var_record, var);
	else
		ft_extend_env(c_env, var);
	free(var->key);
	free(var->value);
	free(var);
}

char	**get_existing_var_record(char **env, char *var_key)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_substr(env[i], 0, ft_strlen(var_key)), var_key) == 0)
		{
			if (env[i][ft_strlen(var_key)] == '=')
				return (&env[i]);
		}
		i++;
	}
	return (NULL);
}
