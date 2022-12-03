/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/12/03 01:36:23 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	put_parent_pipe(t_data *data, t_cmd *cmd)
{
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (cmd->input && cmd->input->operator == PIPE_R)
		in = cmd->input->fd;
	if (cmd->output && cmd->output->operator == PIPE_R)
		out = cmd->output->fd;
	set_parent_new_in_out(data, in, out);
}

static void	reset_parent_in_out(t_data *data, t_cmd *cmd)
{
	if (cmd->input && cmd->input->operator == PIPE_R
		&& cmd->input->fd > -1)
	{
		close(cmd->input->fd);
		cmd->input->fd = -1;
	}
	if (cmd->output && cmd->output->operator == PIPE_R
		&& cmd->output->fd > -1)
	{
		close(cmd->output->fd);
		cmd->output->fd = -1;
	}
	set_parent_default_in_out(data);
}

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
	signal(SIGQUIT, &replace_sig_quit);
	signal(SIGINT, &replace_sig_int_exe);
	exec_loop(data, data->commands, 0);
	close_all_fd(data->commands);
	wait_process(data->commands);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &replace_sig_int);
}
