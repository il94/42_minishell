/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:48:10 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/01 14:37:33 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
