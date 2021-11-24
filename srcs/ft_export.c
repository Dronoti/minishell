#include "minishell.h"

typedef struct s_var
{
	int key_len;
	int value_len;
	char *key;
	char *value;
} t_var;

int is_valid_var_key(char *key);

char	*get_word_end(char *s, char c)
{
	if ((char *)ft_memchr(s, c, ft_strlen(s)) == 0)
		return ((char *)ft_memchr(s, '\0', ft_strlen(s) + 1));
	return ((char *)ft_memchr(s, c, ft_strlen(s)));
}

void	ft_extend_env(char ***env, t_var *new_var)
{
	char	**copy;
	int		i;
	char *tmp_var_str;
	char *new_var_str;

	g_code = 0;
	i = 0;
	while ((*env)[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 2));
	if (!copy)
		ft_errors("Malloc error", 1);

	i = copy_env_vars(copy, *env);
	ft_free_env(*env);
	tmp_var_str = ft_strjoin(new_var->key, "=");
	if (!tmp_var_str)
	{
		ft_free_env(copy);
		ft_errors("Malloc error", 1);
	}
	new_var_str = ft_strjoin(tmp_var_str, new_var->value);
	if (!new_var_str)
	{
		free(tmp_var_str);
		ft_free_env(copy);
		ft_errors("Malloc error", 1);
	}
	free(tmp_var_str);
	copy[i] = new_var_str;
	copy[i + 1] = NULL;
	*env = copy;
}

int setup_var(t_var *var, char **env_var_str)
{
	if (ft_strcmp(get_word_end(*env_var_str, '='), *env_var_str) == 0)
	{
		var->key_len = ft_strlen(*env_var_str);
		var->value_len = 0;
	}
	else if (get_word_end(*env_var_str, '=') - *env_var_str + 1 == ft_strlen(*env_var_str))
	{
		var->key_len = ft_strlen(*env_var_str) - 1;
		var->value_len = 0;
	}
	else
	{
		var->key_len = get_word_end(*env_var_str, '=') - *env_var_str;
		var->value_len = env_var_str[ft_strlen(*env_var_str) - 1] - get_word_end(*env_var_str, '=');
	}
	if (!(var->key = ft_strndup(*env_var_str, var->key_len)))
		return (0);
	// может var->value вообще не нужен?
	if (!(var->value = ft_strndup(*env_var_str + var->key_len + 1 , var->value_len)))
	{
		free(var->key);
		return (0);
	}
	return (1);
}

int ft_export(char **args, int fd, char ***c_env)
{
	int i;
	t_var *variable;

//	i = 0;
//	while ((*c_env)[i] != NULL)
//	{
//		printf("c_env %s\n", (*c_env)[i]);
//		i++;
//	}

	(void)fd;
	if (args[1] == NULL)
	{
		printf("Print all declare x-s");
		return (1);
	}
	i = 1;
	while(args[i] != NULL)
	{
		if (ft_strcmp(get_word_end(args[i], '='), "\0") == 0)
			return (1);
		variable = malloc(sizeof(t_var));
		if (!variable || !setup_var(variable, &args[i]))
			return ft_write_error();
		if (!is_valid_var_key(variable->key))
			printf("is not valid key %s", variable->key);
		printf("key: %s\n", variable->key);
		printf("value: %s\n", variable->value);
		ft_extend_env(c_env, variable);

//		int k = 0;
//		while ((*c_env)[k])
//		{
//			if (ft_strcmp((*c_env)[k], "PATH=/Users/timur/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Users/timur/Library/Python/3.8/bin") == 0)
//				(*c_env)[k][0] = 'U';
//			printf("kcenv %s\n", (*c_env)[k]);
//			k++;
//		}
//			printf("value: %s\n", variable->value);
//			if (!is_valid_var_key(assignment[0]))
//				printf("invalid var key\n");
		i++;
	}


	return (1);
}

int is_valid_var_key(char *key)
{
	int	i;

	if (key[0] >= '0' && key[0] <= '9')
		return (0);
	i = 0;
	while (key[i] != '\0')
	{
		if (key[i] == '_')
			continue;
		if (key[i] < '0' || (key[i] > '9' && key[i] < 'A'))
			return (0);
		if ((key[i] > 'Z' && key[i] < 'a') || key[i] > 'z')
			return (0);
		i++;
	}
	return (1);
}