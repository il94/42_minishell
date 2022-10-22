/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/22 12:00:45 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_data *data)
{
	while (1)
	{
		data->prompt = readline("minishellent> ");
		test_apply(data->prompt);
		/*t_lex *ls = send_dir_content(data->prompt, data, 0);
		ft_lstprint_lex(ls);
		ft_lstclear_lex(&ls);*/
		/*
		if (!ft_strcmp(data->prompt, "stop"))
		{
			free(data->prompt);
			data->prompt = NULL;
			break ;
		}
		if (data->prompt[0] != '\0')
		{	
			add_history(data->prompt);
			get_lexer(data);
			ft_lstprint_lex(data->lexer);
			if (data->lexer)
			{
				lexer(data);
				print_cmd(data->commands, "PARENT");
				parser(data);
			}
			g_exit_status = 0;
		}*/
		free_data_struct(data);
	}
}
