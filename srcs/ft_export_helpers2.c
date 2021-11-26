
#include "minishell.h"

int write_single_var_line(int fd, t_var *var, char *var_str)
{
	if (write(fd, "declare -x ", ft_strlen("declare -x ")) == -1)
		return ft_write_error();
	if (write(fd, var->key, ft_strlen(var->key)) == -1)
		return ft_write_error();
	if (*(var_str + ft_strlen(var->key)) == '=')
	{
		if(write(fd, "=\"", sizeof("\"")) == -1)
			return ft_write_error();
		if(write(fd, var->value, sizeof(char) * ft_strlen(var->value)) == -1)
			return ft_write_error();
		if(write(fd, "\"", sizeof("\"")) == -1)
			return ft_write_error();
	}
	if (write(fd, "\n", sizeof("\n")) == -1)
		return ft_write_error();
	return (1);
}
