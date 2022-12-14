/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:48:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 17:09:18 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace_sig_int_exe(int signum)
{
	(void)signum;
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
