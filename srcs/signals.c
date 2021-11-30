/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkael <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:08:51 by bkael             #+#    #+#             */
/*   Updated: 2021/11/21 19:09:10 by bkael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_handler(int signum)
{
	(void)signum;
	g_code = 130;
	write(1, "\n", 1);
}

void	ft_handler(int signum)
{
	(void)signum;
	g_code = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_child_exit(int signum)
{
	(void)signum;
	g_code = 130;
	write(1, "\n", 1);
	exit(130);
}
