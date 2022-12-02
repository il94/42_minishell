/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:02 by auzun             #+#    #+#             */
/*   Updated: 2022/12/02 19:36:55 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_process(t_cmd *commands)
{
	t_cmd	*cmd;
	int		status_code;
	int		wstatus;

	if (!commands)
		return ;
	status_code = 0;
	wstatus = 0;
	cmd = commands;
	while (cmd)
	{
		if (cmd->pid != -42)
		{
			waitpid(cmd->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				status_code = WEXITSTATUS(wstatus);
			if (g_exit_status != 130 && g_exit_status != 131
				&& !is_builtin_parent(cmd->command))
				g_exit_status = status_code;
			cmd->pid = -42;
		}
		if (cmd->child_cmd)
			wait_process(cmd->child_cmd);
		cmd = cmd->next;
	}
}
