/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 18:38:02 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_lexer(t_data *data)
{
	data->lexer = NULL;
	data->lexer = ft_lstsplit_charset_lex(data->prompt, "><&|() \t$\'\"");
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
		if (!ft_strcmp(data->lexer->str, "&"))
		{
			printf("ERROR\n");
			break ;
		}
		define_delimiter(data);
		if (data->commands->prev && data->commands->prev->delimiter)
			printf("delimiterent = %d\n", data->commands->prev->delimiter);
		define_redi(data);
		if (data->commands->input)
			printf("inpu = %s\n", data->commands->input->file);
		if (data->commands->output)
			printf("outepu = %s\n", data->commands->output->file);
		else if (data->commands->prev && data->commands->prev->output)
			printf("prev outepu = %s\n", data->commands->prev->output->file);
		data->lexer = data->lexer->next;
		// define_command(data);
	}
	data->lexer = data->start_lex;
	data->commands = data->start_cmd;
}
