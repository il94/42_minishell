/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:54:26 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 22:33:44 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	define_command(t_data *data)
{
	t_lex	*temp;

	if (!data->lexer || !data->commands
		|| (data->commands && data->commands->command))
		return (0);
	if (!is_token(data->lexer) && !ft_iswhitespace(data->lexer->str[0])
		&& ft_strcmp(data->lexer->str, "(") && ft_strcmp(data->lexer->str, ")"))
	{
		temp = data->lexer->prev;
		while (temp && temp->str[0] == ' ')
			temp = temp->prev;
		if ((get_redi(temp) != NOTHING_R && get_redi(temp) != PIPE_R))
			return (0);
		data->commands->command = ft_strdup(data->lexer->str);
		if (!data->commands->command)
			free_all_and_exit(data, "malloc");
		return (1);
	}
	return (0);
}
