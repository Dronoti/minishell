
#include "minishell.h"

int	ft_pwd(char **args, int *fd)
{
	(void)args;
	char *path;
	int i;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (-1);

	i = 0;
	while (fd[i])
	{
		write(fd[i], path, ft_strlen(path));
		write(fd[i], "\n", 1);
		i++;
	}
	return (1);
}
