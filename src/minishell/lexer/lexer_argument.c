/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:25:21 by auzun             #+#    #+#             */
/*   Updated: 2022/11/21 16:44:25 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* la meme fonction que define command avec une petite diff qui est qu on stock
tout dans un t_lex... pour faciliter la tache....*/
int	define_argument(t_data *data)
{
	t_lex	*temp;
	t_lex	*new;

	if (!data->commands || !data->commands->command)
		return (0);
	if (!is_token(data->lexer) && !ft_iswhitespace(data->lexer->str[0])
		&& ft_strcmp(data->lexer->str, "(") && ft_strcmp(data->lexer->str, ")"))
	{
		temp = data->lexer->prev;
		while (temp && temp->str[0] == ' ')
			temp = temp->prev;
		if ((get_redi(temp) != NOTHING_R && get_redi(temp) != PIPE_R))
			return (0);
		new = ft_lstnew_lex_dup(ft_strdup(data->lexer->str));
		if (!new || !new->str)
			free_all_and_exit(data, "malloc");
		ft_lstadd_back_lex(&(data->commands->args), new);
		return (1);
	}
	return (0);
}
