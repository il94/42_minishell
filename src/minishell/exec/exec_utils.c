/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:00:42 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 21:33:22 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_fd	*get_cmd_in_or_out(t_fd *file, int is_input)
{
	t_fd	*fd;

	fd = NULL;
	if (is_input)
	{
		fd = file;
		while (fd && fd->next)
			fd = fd->next;
	}
	else
	{
		fd = file;
		while (fd
			&& (fd->next && fd->next->operator != PIPE_R))
			fd = fd->next;
	}
	return (fd);
}

void	put_parent_pipe(t_data *data, t_cmd *cmd)
{
	int		in;
	int		out;
	t_fd	*fd;

	in = -1;
	out = -1;
	fd = get_cmd_in_or_out(cmd->input, 1);
	if (fd && fd->fd > -1)
		in = fd->fd;
	fd = get_cmd_in_or_out(cmd->output, 0);
	if (fd && fd->fd > -1)
		out = fd->fd;
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
