/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:03:41 by auzun             #+#    #+#             */
/*   Updated: 2022/11/18 13:10:56 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parsing_file_name(t_data *data, t_fd *file)
{
	t_lex	*lst;

	lst = NULL;
	if (!file)
		return ;
	if (file->file
		&& (ft_strchr(file->file, '\"') || ft_strchr(file->file, '\'')
			|| ft_strchr(file->file, '$') || ft_strchr(file->file, '*')))
		lst = check_str(data, file->file);
	if (!lst)
		return ;
	if (lst->next)
	{
		g_exit_status = 1;
		msg_error("minishell: ");
		msg_error(file->file);
		msg_error(": ambiguous redirect\n");
		ft_lstclear_lex(&lst);
		return ;
	}
	free(file->file);
	file->file = ft_strdup(lst->str);
	ft_lstclear_lex(&lst);
	if (!file->file)
		free_all_and_exit(data, "malloc");
}

static void	parsing_files(t_data *data, t_fd *files)
{
	t_fd	*f;

	if (!files)
		return ;
	f = files;
	while (f)
	{
		parsing_file_name(data, f);
		if (g_exit_status)
			return ;
		f = f->next;
	}
}

void	parser_input_output(t_data *data, t_cmd *cmd)
{
	if (cmd->input)
		parsing_files(data, cmd->input);
	if (g_exit_status)
		return ;
	if (cmd->output)
		parsing_files(data, cmd->output);
}
