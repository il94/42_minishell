/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/17 20:07:29 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_data *data)
{
	while (1)
	{
		data->prompt = readline("minishellent> ");
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
			// ft_lstprint_lex(data->lexer);
			if (data->lexer)
				lexer(data);			
		}
		printf("addr = %p\n", data->commands->next->input);
		printf("addr = %p\n", data->commands->output);
		free_data_struct(data);
	}
}
