/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialize_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:36 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 17:27:43 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	concat_element(t_lex **lexer, t_bool is_prev)
{
	if (is_prev)
		(*lexer) = (*lexer)->prev;
	(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
	if (!(*lexer)->str)
		return (0);
	ft_lstdelone_lex((*lexer)->next);
	return (1);
}

int	search_closing_quote(t_lex *lexer)
{
	while (lexer)
	{
		if (is_in_quotes(&lexer->str[0], &lexer->str[ft_strlen(lexer->str)]))
			return (0);
		lexer = lexer->next;
	}
	return (1);
}

int	search_closing_parenthese(t_lex *lexer)
{
	int		opened;
	int		closed;

	opened = 0;
	closed = 0;
	while (lexer)
	{
		if (!is_there(QUOTES, lexer->str[0]) && is_there(lexer->str, '('))
			opened++;
		if (!is_there(QUOTES, lexer->str[0]) && is_there(lexer->str, ')'))
			closed++;
		if (closed > opened)
			return (1);
		lexer = lexer->next;
	}
	return (closed - opened);
}
