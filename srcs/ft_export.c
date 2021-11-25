#include "minishell.h"

typedef struct s_var
{
	int key_len;
	int value_len;
	char *key;
	char *value;
} t_var;

int is_valid_var_key(char *key);

char	*get_str_from_symbol(char *s, char c)
{
	if ((char *)ft_memchr(s, c, ft_strlen(s)) == 0)
		return ((char *)ft_memchr(s, '\0', ft_strlen(s) + 1));
	return ((char *)ft_memchr(s, c, ft_strlen(s)));
}

char **get_existing_var_record(char **env, char *var_key)
{
	int		i;

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

void update_var(char **existing_var_record, t_var *new_var)
{
	char *tmp;
	char *new_var_str;

	tmp = ft_strjoin(new_var->key, "=");
	if (!tmp)
		ft_errors("Malloc error", 1);
	new_var_str = ft_strjoin(tmp, new_var->value);
	if (!new_var_str)
		ft_errors("Malloc error", 1);
	free(tmp);
	tmp = NULL;
	tmp = *existing_var_record;
	*existing_var_record = new_var_str;
	free(tmp);
}

void	ft_extend_env(char ***env, t_var *new_var)
{
	char	**copy;
	int		i;
	char **new_var_str;

	g_code = 0;
	i = 0;
	while ((*env)[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 2));
	if (!copy)
		ft_errors("Malloc error", 1);
	i = copy_env_vars(copy, *env);
	new_var_str = malloc(sizeof(char *));
	update_var(new_var_str, new_var);
	// надо еще очищать copy:
	if (!new_var_str)
		ft_errors("Malloc error", 1);
	ft_free_env(*env);
	copy[i] = *new_var_str;
	copy[i + 1] = NULL;
	*env = copy;
}

void setup_var(t_var *var, char **env_var_str)
{
	if (ft_strcmp(get_str_from_symbol(*env_var_str, '='), *env_var_str) == 0)
	{
		var->key_len = ft_strlen(*env_var_str);
		var->value_len = 0;
	}
	else if (get_str_from_symbol(*env_var_str, '=') - *env_var_str + 1 == ft_strlen(*env_var_str))
	{
		var->key_len = ft_strlen(*env_var_str) - 1;
		var->value_len = 0;
	}
	else
	{
		var->key_len = get_str_from_symbol(*env_var_str, '=') - *env_var_str;
		var->value_len = (int)(*env_var_str + (ft_strlen(*env_var_str) - 1) - get_str_from_symbol(*env_var_str, '='));
	}
	if (!(var->key = ft_strndup(*env_var_str, var->key_len)))
		ft_errors("Malloc error", 1);
	if (!(var->value = ft_strndup(*env_var_str + var->key_len + 1 , var->value_len)))
		ft_errors("Malloc error", 1);
}

int ft_export(char **args, int fd, char ***c_env)
{
	int i;
	t_var *var;
	char **existing_var_record;

	(void)fd;
	if (args[1] == NULL)
	{
		printf("Print all declare x-s");
		return (1);
	}
	i = 1;
	while(args[i] != NULL)
	{
		if (ft_strcmp(get_str_from_symbol(args[i], '='), "\0") == 0)
		{
			i++;
			continue ;
		}
		var = malloc(sizeof(t_var));
		if (var == NULL)
			ft_errors("Malloc error", 1);
		setup_var(var, &(args[i]));
		if (!is_valid_var_key(var->key))
		{
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		if((existing_var_record = get_existing_var_record(*c_env, var->key)))
			update_var(existing_var_record, var);
		else
			ft_extend_env(c_env, var);
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