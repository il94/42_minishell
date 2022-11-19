/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:35:05 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/19 13:01:33 by auzun            ###   ########.fr       */
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
		data->commands = data->commands->next;
	}
}
