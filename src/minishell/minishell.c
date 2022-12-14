/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/09 15:19:37 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_prompt(t_data *data)
{
	get_lexer(data);
	if (data->lexer)
	{
		lexer(data);
		if (!g_exit_status)
			parser(data);
		if (!g_exit_status)
			exec(data);
	}
}

void	minishell(t_data *data)
{
	while (1)
	{
		data->prev_exit_status = g_exit_status;
		g_exit_status = 0;
		data->prompt = readline("minishell> ");
		if (g_exit_status >= 130)
		{
			data->prev_exit_status = g_exit_status;
			g_exit_status = 0;
		}
		if (!data->prompt)
			free_all_and_exit(data, "exit");
		if (data->prompt[0] != '\0')
		{	
			add_history(data->prompt);
			read_prompt(data);
		}
		free_data_struct(data);
	}
}
