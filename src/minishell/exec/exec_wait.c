/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:02 by auzun             #+#    #+#             */
/*   Updated: 2022/12/03 00:46:34 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	catch_child_status(int wstatus, char *command)
{
	int	status_code;

	status_code = 0;
	if (WIFSIGNALED(wstatus))
	{
		status_code = WTERMSIG(wstatus);
		if (status_code == 2)
			g_exit_status = 130;
		else if (status_code == 3)
			g_exit_status = 131;
		return ;
	}
	else if (WIFEXITED(wstatus))
		status_code = WEXITSTATUS(wstatus);
	if (!is_builtin_parent(command))
		g_exit_status = status_code;
}

void	wait_process(t_cmd *commands)
{
	t_cmd	*cmd;
	int		wstatus;

	if (!commands)
		return ;
	wstatus = 0;
	cmd = commands;
	while (cmd)
	{
		if (cmd->pid != -42)
		{
			waitpid(cmd->pid, &wstatus, 0);
			catch_child_status(wstatus, cmd->command);
			cmd->pid = -42;
		}
		if (cmd->child_cmd)
			wait_process(cmd->child_cmd);
		cmd = cmd->next;
	}
}
