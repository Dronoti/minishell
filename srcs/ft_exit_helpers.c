/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timur <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 03:38:39 by timur             #+#    #+#             */
/*   Updated: 2021/11/28 03:38:41 by timur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_exit_error_numeric_argument_required(char *first_arg)
{
	write(2, MSG_MINISHELL_EXIT, ft_strlen(MSG_MINISHELL_EXIT));
	write(2, first_arg, ft_strlen(first_arg));
	write(2, NUM_ARG_REQUIRED_MSG, ft_strlen(NUM_ARG_REQUIRED_MSG));
	g_code = 255;
	exit(g_code);
}

void	exit_on_too_many_args(void)
{
	g_code = 1;
	ft_putendl_fd("bash: exit: too many arguments", 2);
	exit(g_code);
}
