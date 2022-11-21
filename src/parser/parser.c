/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:58:16 by auzun             #+#    #+#             */
/*   Updated: 2022/11/21 16:46:11 by ilandols         ###   ########.fr       */
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
		msg_error \
			("minishell: syntax error (minishell) near unexpected token `");
	msg_error(deli);
	msg_error("'\n");
	define_exit_status(NULL, 2);
}

static void	empty_cmd(t_data *data, t_cmd *command)
{
	t_cmd	*cmd;

	if (!command)
		return ;
	cmd = command;
	while (cmd)
	{
		if (!cmd->command && !cmd->child_cmd
			&& (!cmd->input || cmd->input->operator == PIPE_R)
			&& (!cmd->output || cmd->output->operator == PIPE_R))
		{
			if (cmd->delimiter != NOTHING_D)
				unexpected_token(cmd->delimiter, 0);
			else if (cmd->prev)
				unexpected_token(cmd->prev->delimiter, 1);
			if (g_exit_status)
				return ;
		}
		cmd = cmd->next;
	}
}

static void	invalid_child(t_data *data, t_cmd *command)
{
	t_cmd	*cmd;
	int		is_invalid;

	is_invalid = 0;
	if (!command || !command->child_cmd)
		return ;
	cmd = command->child_cmd;
	if (command->command && cmd)
		is_invalid = 1;
	while (cmd)
	{
		if (cmd->delimiter == PIPE_D)
			is_invalid = 1;
		cmd = cmd->next;
	}
	if (is_invalid)
	{
		msg_error("minishell: syntax error (minishell) ");
		msg_error("invalid use of parentheses\n");
		define_exit_status(NULL, 2);
	}
	return ;
}

void	parser(t_data *data, t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	if (!data || !cmd || g_exit_status)
		return ;
	empty_cmd(data, cmd);
	if (g_exit_status)
		return ;
	invalid_child(data, cmd);
	if (g_exit_status)
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
