/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:06:29 by auzun             #+#    #+#             */
/*   Updated: 2022/11/15 21:40:15 by auzun            ###   ########.fr       */
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

void	parsing_file_name(t_data *data, t_cmd *command, t_fd *file/*, int in_out*/)
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
		/*ambiguous redirect*/
		return;
	}
	file->file = ft_strdup(lst->str);
	ft_lstclear_lex(&lst);
	if (!file->file)
		free_all_and_exit(data, "malloc");
}

t_lex	*parsing_cmd(t_data *data, t_cmd *command, char *cmd)
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
	tmp = lst->next;
	ft_lstdelone_lex(lst);
	lst = tmp;
	if (!command->command)
	{
		ft_lstclear_lex(&lst);
		free_all_and_exit(data, "malloc");
	}
	return (lst);
}

/*void parsing_args(t_data *data, t_cmd *command, t_lex *args, t_lex *before)
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
	tmp = lst->next;
	ft_lstdelone_lex(lst);
	lst = tmp;
	if (!command->command)
	{
		ft_lstclear_lex(&lst);
		free_all_and_exit(data, "malloc");
	}
	return (lst);
}*/