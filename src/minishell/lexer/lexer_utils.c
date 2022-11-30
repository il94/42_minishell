/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 17:27:38 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token(t_lex *element)
{
	return (get_delimiter(element) || get_redi(element));
}

t_redi	get_redi(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_R);
	if (!ft_strcmp(element->str, "<"))
		return (L_CHEVRON);
	if (!ft_strcmp(element->str, "<<"))
		return (L_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, ">"))
		return (R_CHEVRON);
	if (!ft_strcmp(element->str, ">>"))
		return (R_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_R);
	return (NOTHING_R);
}

t_deli	get_delimiter(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_D);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_D);
	if (!ft_strcmp(element->str, "&&"))
		return (AND);
	if (!ft_strcmp(element->str, "||"))
		return (OR);
	return (NOTHING_D);
}
