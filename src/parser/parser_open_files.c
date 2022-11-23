/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:24:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/23 16:53:16 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void open_files_loop(t_data *data, t_fd *lst_file)
{
	t_fd *lst;  
	lst = lst_file;
	while (lst)
	{
		if (lst->operator == L_CHEVRON)
			lst->fd = open(lst->file, O_RDONLY, 0644);
	   	else if (lst->operator== L_DOUBLE_CHEVRON)
			generate_here_doc(data, lst);
		else if (lst->operator == R_CHEVRON)
			lst->fd = open(lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (lst->operator == R_DOUBLE_CHEVRON)
			lst->fd = open(lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (lst->file && lst->fd < 0)
			perror(lst->file);
		lst = lst->next;
	}
}

void	open_files(t_data *data, t_cmd *cmd)
{
	t_cmd *lst_cmd;

	 lst_cmd = cmd;
	while (lst_cmd)
	{
		if (lst_cmd->input)
			open_files_loop(data, lst_cmd->input);
		if (lst_cmd->output)
			open_files_loop(data, lst_cmd->output);
		lst_cmd = lst_cmd->next;
	}
}
