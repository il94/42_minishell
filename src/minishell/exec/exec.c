/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/12/04 17:23:02 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_loop(t_data *data, t_cmd *commands, int is_child)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (!is_child && cmd->child_cmd)
			put_parent_pipe(data, cmd);
		if ((is_child || !cmd->child_cmd)
			&& !launch_command(data, cmd))
			break ;
		if (cmd->child_cmd)
			exec_loop(data, cmd->child_cmd, 1);
		if (!is_child && cmd->child_cmd)
			reset_parent_in_out(data, cmd);
		cmd = cmd->next;
	}
}

void	exec(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &replace_sig_int_exe);
	exec_loop(data, data->commands, 0);
	close_all_fd(data->commands);
	wait_process(data, data->commands, get_last_cmd(data->commands));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &replace_sig_int);
}
