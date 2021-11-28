/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 03:37:34 by timur             #+#    #+#             */
/*   Updated: 2021/11/28 03:37:36 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int				check_arg1(char *const *args);
void			write_exit_error_numeric_argument_required(char *first_arg);
void			exit_on_too_many_args(void);
long long int	get_first_arg_number(char *first_arg);
long long int	count_result(const char *first_arg, long long result, int i);

int	ft_exit(char **args)
{
	int			first_arg_len;
	long long	result;

	g_code = 0;
	write(2, "exit\n", ft_strlen("exit\n"));
	if (args[1] == NULL)
		exit(g_code);
	first_arg_len = check_arg1(args);
	if (args[2] != NULL)
		exit_on_too_many_args();
	if ((args[1][0] == '-' && first_arg_len > 20)
		|| (args[1][0] != '-' && first_arg_len > 19))
		write_exit_error_numeric_argument_required(args[1]);
	result = get_first_arg_number(args[1]);
	g_code = (int)(result % 256);
	exit(g_code);
}

long long int	get_first_arg_number(char *first_arg)
{
	long long int	result;
	int				i;

	i = 0;
	if (first_arg[0] == '-')
		i++;
	result = 0;
	while (first_arg[i])
	{
		if (result < (LONG_MIN / 10))
			write_exit_error_numeric_argument_required(first_arg);
		if (first_arg[0] == '-'
			&& (result == (LONG_MIN / 10)) && (((int) first_arg[i] - 48) > 8))
			write_exit_error_numeric_argument_required(first_arg);
		if (result > (LONG_MAX / 10))
			write_exit_error_numeric_argument_required(first_arg);
		if (first_arg[0] != '-'
			&& (result == (LONG_MAX / 10)) && (((int) first_arg[i] - 48) > 7))
			write_exit_error_numeric_argument_required(first_arg);
		result = count_result(first_arg, result, i);
		i++;
	}
	return (result);
}

long long int	count_result(const char *first_arg, long long int result, int i)
{
	if (first_arg[0] == '-')
		result = (result * 10) - ((int)first_arg[i] - 48);
	else
		result = (result * 10) + ((int)first_arg[i] - 48);
	return (result);
}

int	check_arg1(char *const *args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (i == 0 && args[1][i] == '-')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(args[1][i]))
		{
			g_code = 255;
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			exit(g_code);
		}
		i++;
	}
	return (i);
}
