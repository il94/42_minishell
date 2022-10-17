/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/17 19:05:53 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redi	define_redi(t_lex *element)
{
	if (!element || !element->content)
		return (NOTHING_R);	
	if (!ft_strcmp(element->content, "<"))
		return (L_CHEVRON);
	if (!ft_strcmp(element->content, "<<"))
		return (L_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->content, ">"))
		return (R_CHEVRON);
	if (!ft_strcmp(element->content, ">>"))
		return (R_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->content, "|"))
		return (PIPE_R);
	return (NOTHING_R);	
}

t_delimiter	get_delimiter(t_lex *element)
{
	if (!ft_strcmp(element->content, "|"))
		return (PIPE_D);
	if (!ft_strcmp(element->content, "&&"))
		return (AND);
	if (!ft_strcmp(element->content, "||"))
		return (OR);
	if (!ft_strcmp(element->content, ")"))
		return (P_CLOSED);
	if (!ft_strcmp(element->content, "("))
		return (P_OPENED);
	return (NOTHING_D);
}

int	is_token(t_lex *element, char *c, char *charset)
{
	if (ft_strlen(c) == 1 && element->content[0] == *c
		&& (!element->next || element->next->content[0] != *c))
		return (element->content[0] == *c && (!element->next
				|| (!is_there(charset, element->next->content[0]))));
	else
	{
		return (element->content[0] == c[0]
			&& (element->next && element->next->content[0] == c[1])
			&& (!element->next->next
			|| !is_there(charset, element->next->next->content[0])));
	}
}

int	is_there(char *str, char in)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in == str[i])
			return (str[i]);
		i++;
	}
	return (0);
}
