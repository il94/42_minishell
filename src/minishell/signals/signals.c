/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:48:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/01 14:37:06 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_sig_quit(int signum)
{
	(void)signum;
	g_exit_status = 131;
	ft_printf_fd(2, "Quit (core dumped)\n");
}

void	replace_sig_int_exe(int signum)
{
	(void)signum;
	g_exit_status = 130;
	ft_printf_fd(2, "\n");
}

void	replace_sig_int(int signum)
{
	(void)signum;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}
