/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:43:31 by ilyes             #+#    #+#             */
/*   Updated: 2022/11/14 02:09:52 by auzun            ###   ########.fr       */
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

