/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/02 15:44:55 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_lexer(t_data *data)
{
	data->lexer = NULL;
	data->lexer = ft_lstsplit_charset_lex(data->prompt, " \t\n\v\f\r><&|()$\'\"");
	if (!data->lexer)
		free_all_and_exit(data, "malloc");
	data->start_lex = data->lexer;
	if (!concat_lexer(data))
		free_lexer_struct(&(data->start_lex));
	data->lexer = data->start_lex;
}

void	lexer(t_data *data)
{
	data->commands = ft_lstnew_cmd();
	if (!data->commands)
		free_all_and_exit(data, "malloc");
	data->start_cmd = data->commands;
	while (data->lexer)
	{
		define_child(data);
		define_delimiter(data);
		define_redi(data);
		if (g_exit_status)
			break ;
		define_argument(data);
		define_command(data);
		if (data->lexer)
			data->lexer = data->lexer->next;
	}
	data->lexer = data->start_lex;
	data->commands = data->start_cmd;
}
