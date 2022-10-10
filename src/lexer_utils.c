/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/10 16:50:13 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
