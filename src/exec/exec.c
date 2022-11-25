/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/11/25 20:59:44 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	is_builtin(t_data )*/

int	verif_files_fd (t_fd *in, t_fd *out)
{
	t_fd	*fd_in;
	t_fd	*fd_out;

	fd_in = NULL;
	fd_out = NULL;
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

void	dup2_r_and_w(t_fd *in, t_fd *out)
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
	if (fd_in->fd)
		dup2(fd_in->fd, 0);
	if (fd_out->fd)
		dup2(fd_out->fd, 1);
}

/*the pipe create a subshell so when we have || or && we dont fork...*/
void	launch_command(t_data *data, t_cmd *command)
{
	int	is_there_pipe;

	is_there_pipe = 0;
	if (command->delimiter == PIPE_D
		|| (command->prev && command->delimiter == PIPE_D))
	{
		command->pid = fork();
		if (command->pid == -1)
			free_all_and_exit(data, "fork");
		is_there_pipe = 1;
	}
	if (command->pid == 0 || !is_there_pipe)
	{
		if (!verif_files_fd(command->input, command->output))
			return ;
		dup2_r_and_w(command->input, command->output);
	}
}

// void	exec(t_data *data, t_cmd *commands)
// {
// 	t_cmd	*cmd;

// 	cmd = commands;
// 	while (cmd)
// 	{
		
// 	}
// }