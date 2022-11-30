/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:43:31 by ilyes             #+#    #+#             */
/*   Updated: 2022/11/30 23:16:16 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	*ft_lstnew_lex(char *str)
{
	t_lex	*element;

	if (!str)
		return (NULL);
	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->str = str;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}

t_lex	*ft_lstnew_lex_dup(char *str)
{
	t_lex	*element;

	if (!str)
		return (NULL);
	element = malloc(sizeof(*element));
	if (!element)
	{
		free(str);
		return (NULL);
	}
	element->str = str;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}
