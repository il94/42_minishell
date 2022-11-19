/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:58:16 by auzun             #+#    #+#             */
/*   Updated: 2022/11/20 00:02:48 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	unexpected_token(t_deli token, int v_mini)
{
	char	*deli;

	deli = get_deli_char(token);
	if (!deli)
		return ;
	if (!v_mini)
		msg_error("minishell: syntax error near unexpected token `");
	else
		msg_error("minishell: syntax error (minishell) near unexpected token `");
	msg_error(deli);
	msg_error("'\n");
	define_exit_status(NULL, 2);
}

static void	empty_cmd(t_data *data, t_cmd *command)
{
	t_cmd	cmd;

	if (!command)
		return ;
	cmd = *command;
	if (!cmd.command && !cmd.child_cmd
		&& (!cmd.input || cmd.input->operator == PIPE_R)
		&& (!cmd.output || cmd.output->operator == PIPE_R))
	{
		if (cmd.delimiter != NOTHING_D)
			unexpected_token(cmd.delimiter, 0);
		else if (cmd.prev)
			unexpected_token(cmd.prev->delimiter, 1);
	}
}

void	parser(t_data *data, t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	if (!data || !cmd || g_exit_status)
		return ;
	while (cmd)
	{
		empty_cmd(data, cmd);
		if (g_exit_status)
			return ;
		parser_input_output(data, cmd);
		if (g_exit_status)
			return ;
		parser_cmd_arg(data, cmd);
		if (cmd->child_cmd)
			parser(data, cmd->child_cmd);
		cmd = cmd->next;
	}
}
