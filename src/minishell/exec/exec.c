/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/12/01 16:14:56 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_loop(t_data *data, t_cmd *commands)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (!launch_command(data, cmd))
			break ;
		if (cmd->child_cmd)
			exec_loop(data, cmd->child_cmd);
		cmd = cmd->next;
	}
}

void	exec(t_data *data, t_cmd *commands)
{
	signal(SIGQUIT, &replace_sig_quit);
	signal(SIGINT, &replace_sig_int_exe);
	exec_loop(data, commands);
	close_fd(commands);
	wait_process(commands, &data->prev_exit_status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &replace_sig_int);
}
