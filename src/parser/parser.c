/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:58:16 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 08:51:40 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	unexpected_token(t_deli token, int v_mini)
{
	char	*deli;

	deli = get_deli_char(token);
	if (!deli)
		msg_error("minishell: syntax error near unexpected token `('\n"); //faire gafffe au sens de la parenthese ou balec
		// msg_error("minishell: parentheses have to contain '&&' or '||' tokens\n"); //a confirmer
	else if (!v_mini)
		msg_error("minishell: syntax error near unexpected token `");
	else
		msg_error \
			("minishell: syntax error (minishell) near unexpected token `");
	if (deli)
	{
		msg_error(deli);
		msg_error("'\n");
	}
	define_exit_status(NULL, 2);
}

static void	empty_cmd(t_cmd *command, int is_child)
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
			if (cmd->delimiter != NOTHING_D || is_child && !cmd->prev)
				unexpected_token(cmd->delimiter, 0);
			else if (cmd->prev)
				unexpected_token(cmd->prev->delimiter, 1);
			if (g_exit_status)
				return ;
		}
		cmd = cmd->next;
	}
}

static int	is_invalid_child(t_cmd *command)
{
	t_cmd	*cmd;
	int		is_invalid;

	is_invalid = 0;
	if (!command || !command->child_cmd)
		return (1);
	cmd = command->child_cmd;
	if (command->command && cmd)
		is_invalid = 1;
	while (cmd)
	{
		if (cmd->delimiter == PIPE_D)
			is_invalid = 1;
		if (is_invalid || (cmd->child_cmd && is_invalid_child(cmd->child_cmd)))
			break;
		cmd = cmd->next;
	}
	if (is_invalid)
	{
		msg_error("minishell: syntax error (minishell) ");
		msg_error("invalid use of parentheses\n");
		define_exit_status(NULL, 2);
		return (1);
	}
	return (0);
}

static void	invalid_child(t_cmd *command)
{
	t_cmd	*cmd;

	cmd = command;
	while(cmd)
	{
		if (cmd->child_cmd)
			is_invalid_child(cmd);
		if (g_exit_status)
			return ;
		cmd = cmd->next;
	}
}

void	parser(t_data *data, t_cmd *command, int is_child)
{
	t_cmd	*cmd;

	cmd = command;
	if (!data || !cmd || g_exit_status)
		return ;
	empty_cmd(cmd, is_child);
	if (g_exit_status)
		return ;
	invalid_child(cmd);
	if (g_exit_status)
		return ;
	while (cmd)
	{
		parser_input_output(data, cmd);
		if (g_exit_status)
			return ;
		parser_cmd_arg(data, cmd);
		if (cmd->child_cmd)
			parser(data, cmd->child_cmd, 1);
		cmd = cmd->next;
	}
	open_files(data, command);
	if (g_exit_status)
		return ;
	get_all_paths(data);
}
