/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:24:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/22 16:49:51 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void open_files_loop(t_fd *lst_file)
{
    t_fd *lst;

    lst = lst_file;
    while (lst)
    {
        if (lst->operator == L_CHEVRON)
            lst->fd = open(lst->file, O_RDONLY, 0644);
       /* else if (cmd->input->operator == L_DOUBLE_CHEVRON)
            heredoc*/
        else if (lst->operator == R_CHEVRON)
            open(lst->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (lst->operator == R_DOUBLE_CHEVRON)
            open(lst->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (lst->fd < 0)
            perror(lst->file);
        lst = lst->next;
    }
}

void    open_files(t_data *data, t_cmd *cmd)
{
    if (cmd->input)
        open_files_loop(cmd->input);
    if (cmd->output)
         open_files_loop(cmd->output);
}
