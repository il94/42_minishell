/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:24:02 by auzun             #+#    #+#             */
/*   Updated: 2022/11/26 19:04:03 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (cmd->child_cmd)
			wait_process(cmd->child_cmd);
		if (cmd->pid != -42)
		{
			//printf("%d\n", cmd->pid);
			waitpid(cmd->pid, &g_exit_status, 0);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
			printf("[%d]\n", g_exit_status);
			/*if (return_v)
				return (return_v);*/
			//printf("exit status is [%d]\n", g_exit_status);
			cmd->pid = -42;
		}
		cmd = cmd->next;
	}
	return (1);
}