/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/12/02 20:41:57 by auzun            ###   ########.fr       */
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

void	exec(t_data *data)
{
	signal(SIGQUIT, &replace_sig_quit);
	signal(SIGINT, &replace_sig_int_exe);
	exec_loop(data, data->commands);
	close_all_fd(data->commands);
	wait_process(data->commands);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &replace_sig_int);
}
