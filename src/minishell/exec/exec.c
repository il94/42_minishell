/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/12/05 01:35:08 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_parent_before_child(t_data *data, t_cmd *command)
{
	int	is_there_priority;

	is_there_priority = 0;
	if (command->prev && (command->prev->delimiter == AND
			|| command->prev->delimiter == OR))
	{
		is_there_priority = 1;
		wait_process(data, data->commands, get_last_cmd(data->commands));
		if (g_exit_status && red_light(data, command))
			return (0);
	}
	check_cmd_and_fds(data, command);
	if (g_exit_status && is_there_priority
		&& red_light(data, command))
		return (0);
	return (1);
}

static void	exec_loop(t_data *data, t_cmd *commands, int is_child)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (!is_child && cmd->child_cmd)
			put_parent_pipe(data, cmd);
		if (!is_child && cmd->child_cmd
			&& !check_parent_before_child(data, cmd))
			return ;
		if ((is_child || !cmd->child_cmd)
			&& !launch_command(data, cmd))
			return ;
		if (cmd->child_cmd)
			exec_loop(data, cmd->child_cmd, 1);
		if (!is_child && cmd->child_cmd && red_light(data, cmd))
			return ;
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
