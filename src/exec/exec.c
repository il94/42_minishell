/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 08:35:20 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	is_builtin(t_data )*/

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
	//signal(SIGINT, &replace_sig_int);
	exec_loop(data, commands);
	close_fd(commands);
	wait_process(commands, &data->prev_exit_status);
	signal(SIGQUIT, SIG_IGN);
	// printf("actuel = {%d}\n", g_exit_status);
	// printf("prev =   {%d}\n", data->prev_exit_status);
}