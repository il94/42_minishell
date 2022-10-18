/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:54:26 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 19:28:02 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* pour verifier si lst->str == a commande
	je regarde les el precedant en sautant les (whitespaces)
	si el = a redi c est pas bon*/
int	define_command(t_data *data)
{
	t_lex	*temp;

	if (data->commands && data->commands->command)
		return (0);
	if (ft_isalnum(data->lexer->str[0]) || data->lexer->str[0] == '$')
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
