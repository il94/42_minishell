/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:03:41 by auzun             #+#    #+#             */
/*   Updated: 2022/12/02 21:11:37 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ambiguous_redirect(t_fd *file, t_lex *lst)
{
	ft_printf_fd(2, "minishell: %s: ambiguous redirect\n", file->file);
	ft_lstclear_lex(&lst);
	if (file->file)
		free(file->file);
	file->file = NULL;
}

static int	parsing_file_name(t_data *data, t_fd *file)
{
	t_lex	*lst;

	lst = NULL;
	if (!file)
		return (1);
	if (file->file
		&& (file->operator != L_DOUBLE_CHEVRON
			&& (ft_strchr(file->file, '\"') || ft_strchr(file->file, '\'')
				|| ft_strchr(file->file, '$') || ft_strchr(file->file, '*'))))
		lst = check_str(data, file->file);
	if (!lst)
		return (1);
	if (lst->next || (lst->str && !(*lst->str)))
	{
		ambiguous_redirect(file, lst);
		return (0);
	}
	free(file->file);
	file->file = ft_strdup(lst->str);
	ft_lstclear_lex(&lst);
	if (!file->file)
		free_all_and_exit(data, "malloc");
	return (1);
}

static int	parsing_files(t_data *data, t_fd *files)
{
	t_fd	*f;

	if (!files)
		return (1);
	f = files;
	while (f)
	{
		if (!parsing_file_name(data, f))
			return (0);
		f = f->next;
	}
	return (1);
}

int	parser_input_output(t_data *data, t_cmd *cmd)
{
	if (cmd->input)
		parsing_files(data, cmd->input);
	if (cmd->output)
		parsing_files(data, cmd->output);
	return (1);
}
