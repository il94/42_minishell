/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/14 17:35:05 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	define_delimiter(t_data *data)
{
	data->commands->delimiter = get_delimiter(data->lexer);
	if (data->commands->delimiter)
	{
		ft_lstadd_back_cmd(&data->commands, ft_lstnew_cmd());
		if (!data->commands->next)
			free_all_and_exit(data, "malloc");
		if (data->commands->delimiter == AND || data->commands->delimiter == OR)
			data->lexer = data->lexer->next;
		data->commands = data->commands->next;
	}
}


void	lexer(t_data *data)
{
	data->commands = ft_lstnew_cmd();
	if (!data->commands)
		free_all_and_exit(data, "malloc");
	data->start_cmd = data->commands;
	while (data->lexer)
	{
		if (is_token(data->lexer, "&", "&"))
		{
			printf("ERROR\n"); // afficher le bon message
			break ;
		}
		define_delimiter(data);
		/* A effectuer dans define files ou redi */
		// if ((data->data->commands)->delimiter == PIPE_D)
		// 	(data->data->commands)->next->input->operator = PIPE_R;
		data->lexer = data->lexer->next;
	}
	data->lexer = data->start_lex;
}
