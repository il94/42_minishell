/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:02:18 by auzun             #+#    #+#             */
/*   Updated: 2022/11/22 22:13:27 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	define_child(t_data *data)
{
	t_cmd	*current_cmd;
	t_lex	*temp;

	if (!data->lexer || !data->commands)
		return (0);
	if (data->lexer->str[0] == '(')
	{
		current_cmd = data->commands;
		ft_lstadd_back_cmd(&data->commands->child_cmd, ft_lstnew_cmd());
		if (!data->commands->child_cmd)
			free_all_and_exit(data, "malloc");
		data->commands = data->commands->child_cmd;
		while (data->lexer && data->lexer->str[0] != ')')
		{
			data->lexer = data->lexer->next;
			define_child(data);
			define_delimiter(data);
			define_redi(data);
			define_argument(data);
			define_command(data);
		}
		if (data->lexer->str[0] == ')')
			data->lexer = data->lexer->next;
		data->commands = current_cmd;
	}
	return (0);
}
