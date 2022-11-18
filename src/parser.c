/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:58:16 by auzun             #+#    #+#             */
/*   Updated: 2022/11/18 10:18:17 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_data *data, t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	if (!data || !cmd || g_exit_status)
		return ;
	while (cmd)
	{
		parser_input_output(data, cmd);
		if (g_exit_status)
			return ;
		parser_cmd_arg(data, cmd);
		if (cmd->child_cmd)
			parser(data, cmd->child_cmd);
		cmd = cmd->next;
	}
}
