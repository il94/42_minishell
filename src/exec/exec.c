/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/11/26 00:20:43 by auzun            ###   ########.fr       */
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
	if (fd_in)
	{
		printf("in [%d]\n", fd_in->fd);
		dup2(fd_in->fd, 0);
		close(fd_in->fd);
		fd_in->fd = -1;
	}
	if (fd_out)
	{
		printf("out [%d]\n", fd_out->fd);
		dup2(fd_out->fd, 1);
		close(fd_out->fd);
		fd_out->fd = -1;
	}
}

void	close_fd(t_cmd *command)
{
	t_fd	*fd;

	fd = command->input;
	while (fd)
	{
		if (fd->fd > 0)
			close(fd->fd);
		fd->fd = -1;
		fd = fd->next;
	}
	fd = command->output;
	while (fd)
	{
		if (fd->fd > 0)
			close(fd->fd);
		fd->fd = -1;
		fd = fd->next;
	}
}

void	close_all_fd(t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	while (cmd)
	{
		close_fd(cmd);
		cmd = cmd->next;
	}
}

/*a voir si on ajoute le envp ou pas..*/
void	exec_command(t_data *data, t_cmd *command)
{
	char	**args;
	char	**envp;

	args = NULL;

	t_lex *to_add = ft_lstnew_lex(command->command);
	to_add->next = command->args;
	args = ft_lst_lex_to_array(to_add);
	if (!args)
		free_all_and_exit(data, "malloc");
	if (!verif_files_fd(command->input, command->output))
	{
		g_exit_status = 1;
		return ;
	}
	dup2_r_and_w(command->input, command->output);
	close_all_fd(data->commands);
	execve(command->command, args, NULL);
}


/*the pipe create a subshell so when we have || or && we dont fork...*/
void	launch_command(t_data *data, t_cmd *command)
{
	int	is_there_pipe;

	is_there_pipe = 0;
	if (1  == 1/*command->delimiter == PIPE_D
		|| (command->prev && command->delimiter == PIPE_D)*/)
	{
		command->pid = fork();
		if (command->pid == -1)
			free_all_and_exit(data, "fork");
		is_there_pipe = 1;
	}
	if (command->pid == 0 /*|| !is_there_pipe*/)
	{
		exec_command(data, command);
		//if (is_there_pipe)
		free_all_and_exit(data, 0);
	}
	close_fd(command);
}

int	wait_process(t_cmd *commands)
{
	t_cmd	*cmd;
	int		return_v;

	return_v = 0;
	if (!commands)
		return (0);
	cmd = commands;
	while (cmd)
	{
		if (cmd->pid != -42)
		{
			printf("%d\n", cmd->pid);
			waitpid(cmd->pid, &g_exit_status, 0);
			/*if (WIFEXITED(g_exit_status))
				return_v = WEXITSTATUS(g_exit_status);
			if (return_v)
				return (return_v);*/
		}
		cmd = cmd->next;
	}
	return (1);
}

void	exec(t_data *data, t_cmd *commands)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		launch_command(data, cmd);
		cmd = cmd->next;
	}
	close_fd(commands);
	wait_process(commands);
}