/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:24:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/02 20:39:05 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_file(t_data *data, t_fd *file, \
	int is_output, t_cmd *cmd)
{
	if (file->file && file->operator == L_CHEVRON)
			file->fd = open(file->file, O_RDONLY, 0644);
	else if (file->file && file->operator == L_DOUBLE_CHEVRON)
	{
		generate_here_doc(data, file);
		if (g_exit_status)
			return (1);
	}
	else if (file->operator == PIPE_R && is_output)
		generate_pipe(data, file, cmd);
	else if (file->file && file->operator == R_CHEVRON)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file->file && file->operator == R_DOUBLE_CHEVRON)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file->file && file->fd < 0)
	{
		ft_printf_fd(2, "minishell: ");
		perror(file->file);
		return (0);
	}
	return (2);
}

static int	open_files_loop(t_data *data, t_fd *lst_file, \
	int is_output, t_cmd *cmd)
{
	t_fd	*lst;

	lst = lst_file;
	while (lst)
	{
		if (lst->file && is_output && is_dir(lst->file))
			cmd_error(126, lst->file);
		else
			open_file(data, lst, is_output, cmd);
		if (g_exit_status)
			return (130);
		lst = lst->next;
	}
	return (1);
}

void	open_files(t_data *data, t_cmd *cmd)
{
	t_cmd	*lst_cmd;

	lst_cmd = cmd;
	while (lst_cmd)
	{
		if (lst_cmd->child_cmd)
			open_files(data, lst_cmd->child_cmd);
		if (lst_cmd->input)
			open_files_loop(data, lst_cmd->input, 0, lst_cmd);
		if (g_exit_status)
			return ;
		if (lst_cmd->output)
			open_files_loop(data, lst_cmd->output, 1, lst_cmd);
		if (g_exit_status)
			return ;
		lst_cmd = lst_cmd->next;
	}
}
