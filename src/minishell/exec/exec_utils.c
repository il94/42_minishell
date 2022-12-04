/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:00:42 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 17:23:20 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_parent_pipe(t_data *data, t_cmd *cmd)
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

void	reset_parent_in_out(t_data *data, t_cmd *cmd)
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

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	t_cmd	*result;

	result = ft_lstlast_cmd(cmd);
	if (result && result->child_cmd)
		return (get_last_cmd(result->child_cmd));
	return (result);
}
