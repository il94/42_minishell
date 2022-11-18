/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:06:29 by auzun             #+#    #+#             */
/*   Updated: 2022/11/18 04:21:47 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*t_redi	is_there_unexpected_token (t_cmd *command, t_fd *file, int in_out)
{
	if (file->operator != 1 && !file->file)
	{
		if (file->next)
			return (file->next->operator);
		else if(!in_out && command->output)
			return (command->output->operator);
		else if(in_out && command->input)
			return (command->input->operator);
	}
	else if (file->operator == 1 && !in_out && (!file->next && !command->command && !command->output))
}*/

/*void	parsing_file_name(t_data *data, t_cmd *command, t_fd *file)
{
	t_lex	*lst;

	lst = NULL;
	if (!file)
		return ;
	if (file->file && (ft_strchr(file->file, '\"') || ft_strchr(file->file, '\'')
		|| ft_strchr(file->file, '$') || ft_strchr(file->file, '*')))
		lst = check_str(data, file->file);
	if (!lst)
		return ;
	if (lst->next)
	{
		g_exit_status = 1;
		msg_error(file->file);
		msg_error(": ambiguous redirect");
		free_data_struct(data);
		return ;
	}
	file->file = ft_strdup(lst->str);
	ft_lstclear_lex(&lst);
	if (!file->file)
		free_all_and_exit(data, "malloc");
}*/

/*t_lex	*parsing_cmd(t_data *data, t_cmd *command, char *cmd)
{
	t_lex	*lst;
	t_lex	*tmp;

	lst = NULL;
	if (!cmd)
		return (NULL);
	if (cmd && (ft_strchr(cmd, '\"') || ft_strchr(cmd, '\'')
		|| ft_strchr(cmd, '$') || ft_strchr(cmd, '*')))
		lst = check_str(data, cmd);
	if (!lst)
		return (NULL);
	command->command = ft_strdup(lst->str);
	if (!command->command)
	{
		ft_lstclear_lex(&lst);
		free_all_and_exit(data, "malloc");
	}
	tmp = lst->next;
	ft_lstdelone_lex(lst);
	lst = tmp;
	return (lst);
}

static void	add_el_to_arg(t_lex **el, t_lex **cur, t_lex **args)
{
	t_lex *tmp;

	if ((*cur)->prev)
		(*cur)->prev->next = (*first_el(el));
	if ((*cur)->next)
		(*cur)->next->prev = (*last_el(el));
	(*first_el(el))->prev = (*cur)->prev;
	(*last_el(el))->next = (*cur)->next;
	if ((*cur)->next)
		*args = *first_el(&(*cur)->next);
	else if ((*cur)->prev)
		*args = *first_el(&(*cur)->prev);
	else
		*args = *el;
	tmp = (*cur)->next;
	if ((*cur)->str)
		free((*cur)->str);
	free(*cur);
	*cur = tmp;
}

t_lex	*parsing_args(t_data *data, t_cmd *command, t_lex *args, t_lex *before)
{
	t_lex	*lst;
	t_lex	*tmp;
	t_lex	*tmp_arg;

	if (!args && before)
		return (before);
	if (before && args)
	{
		args->prev = (*last_el(&before));
		(*last_el(&before))->next = args;
		lst = args;
		args = before;
	}
	tmp_arg = NULL;
	while (lst)
	{
		if (lst && lst->str && (ft_strchr(lst->str, '\"') || ft_strchr(lst->str, '\'')
			|| ft_strchr(lst->str, '$') || ft_strchr(lst->str, '*')))
		{
				tmp_arg = check_str(data, lst->str);
				if (tmp_arg)
					add_el_to_arg(&tmp_arg, &lst, &args);
		}
		else
			lst = lst->next;
	}
	return (args);
}*/