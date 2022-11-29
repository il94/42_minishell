/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:02 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 08:35:10 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	wait_process(t_cmd *commands, int *prev_exit_status)
{
	t_cmd	*cmd;
	int		status_code;
	int		wstatus;

	if (!commands)
		return (0);
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
			if (g_exit_status != 130 && g_exit_status != 131)
				g_exit_status = status_code;
			// printf("wt = {%d}\n", g_exit_status);
			cmd->pid = -42;
		}
		if (cmd->child_cmd)
			wait_process(cmd->child_cmd, prev_exit_status);
		cmd = cmd->next;
	}
	return (1);
}