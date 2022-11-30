/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 14:36:01 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_data *data)
{
	while (1)
	{
		data->prev_exit_status = g_exit_status;
		g_exit_status = 0;
		data->prompt = readline("\x1b[33msalam khey> \x1b[0m");
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
			get_lexer(data);
			if (data->lexer)
			{
				lexer(data);
				if (!g_exit_status)
					parser(data, data->commands, 0);
				if (!g_exit_status)
					exec(data, data->commands);
			}
		}
		free_data_struct(data);
	}
}
