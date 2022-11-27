/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:25:42 by auzun             #+#    #+#             */
/*   Updated: 2022/11/27 14:58:38 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	is_builtin(t_data )*/

static void	exec_loop(t_data *data, t_cmd *commands)
{
	t_cmd	*cmd;

	cmd = commands;
	while (cmd)
	{
		if (!launch_command(data, cmd))
			break ;
		if (cmd->child_cmd)
		{
			printf("\n=========CHILD============\n");
			exec_loop(data, cmd->child_cmd);
		}
		cmd = cmd->next;
	}
}

void	exec(t_data *data, t_cmd *commands)
{
	exec_loop(data, commands);
	close_fd(commands);
	wait_process(commands);
}