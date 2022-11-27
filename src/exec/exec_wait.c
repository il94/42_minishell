/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:02 by auzun             #+#    #+#             */
/*   Updated: 2022/11/27 15:01:32 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wait_process(t_cmd *commands)
{
	t_cmd	*cmd;
	int		status_code;
	int		wstatus;

	if (!commands)
		return (0);
	cmd = commands;
	while (cmd)
	{
		if (cmd->pid != -42)
		{
			waitpid(cmd->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				status_code = WEXITSTATUS(wstatus);
			if (status_code != 0)
				g_exit_status = status_code;
			cmd->pid = -42;
		}
		if (cmd->child_cmd)
			wait_process(cmd->child_cmd);
		cmd = cmd->next;
	}
	return (1);
}