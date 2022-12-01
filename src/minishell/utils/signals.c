/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:48:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 23:17:13 by ilandols         ###   ########.fr       */
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

void	sig_unexpected_eof(char *delimiter)
{
	ft_printf_fd(2, "\nminishell: warning: here-document delimited by ");
	ft_printf_fd(2, "end-of-file (wanted `%s')\n", delimiter);
}

void	sig_int_heredoc_child(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	close(0);
	g_exit_status = 130;
}

void	sig_int_heredoc_parent(int signum)
{
	(void)signum;
	g_exit_status = 130;
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
