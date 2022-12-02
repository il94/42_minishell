/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:15:50 by auzun             #+#    #+#             */
/*   Updated: 2022/12/02 23:58:59 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	verif_files_fd(t_fd *in, t_fd *out)
{
	t_fd	*fd_in;
	t_fd	*fd_out;

	if (in)
	{
		fd_in = in;
		while (fd_in)
		{
			if (fd_in->fd < 0)
				return (0);
			fd_in = fd_in->next;
		}
	}
	if (out)
	{
		fd_out = out;
		while (fd_out)
		{
			if (fd_out->fd < 0)
				return (0);
			fd_out = fd_out->next;
		}
	}
	return (1);
}

static void	dup2_and_close(t_data *data, t_fd *fd_in, t_fd *fd_out)
{
	if (fd_in && fd_in->fd >= 0)
	{
		dup2(fd_in->fd, 0);
		close(fd_in->fd);
		fd_in->fd = -1;
	}
	else if (data->parent_in_fd > -1)
	{
		dup2(data->parent_in_fd, 0);
		close(data->parent_in_fd);
	}
	if (fd_out && fd_out->fd >= 0)
	{
		dup2(fd_out->fd, 1);
		close(fd_out->fd);
		fd_out->fd = -1;
	}
	else if (data->parent_out_fd > -1)
	{
		dup2(data->parent_out_fd, 1);
		close(data->parent_out_fd);
	}
}

void	dup2_r_and_w(t_data *data, t_fd *in, t_fd *out)
{
	t_fd	*fd_in;
	t_fd	*fd_out;

	fd_in = NULL;
	fd_out = NULL;
	if (in)
	{
		fd_in = in;
		while (fd_in && fd_in->next)
			fd_in = fd_in->next;
	}
	if (out)
	{
		fd_out = out;
		while (fd_out
			&& (fd_out->next && fd_out->next->operator != PIPE_R))
			fd_out = fd_out->next;
	}
	dup2_and_close(data, fd_in, fd_out);
}

void	close_fd(t_cmd *command)
{
	t_fd	*fd;

	fd = command->input;
	while (fd)
	{
		if (fd->fd > -1)
		{
			close(fd->fd);
			fd->fd = -1;
		}
		fd = fd->next;
	}
	fd = command->output;
	while (fd)
	{
		if (fd->fd > -1)
		{
			close(fd->fd);
			fd->fd = -1;
		}
		fd = fd->next;
	}
}

void	close_all_fd(t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	while (cmd)
	{
		if (cmd->child_cmd)
			close_fd(cmd->child_cmd);
		close_fd(cmd);
		cmd = cmd->next;
	}
}
