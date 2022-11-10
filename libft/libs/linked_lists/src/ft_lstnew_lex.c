/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_lex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:43:31 by ilyes             #+#    #+#             */
/*   Updated: 2022/11/10 16:36:57 by ilandols         ###   ########.fr       */
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
