/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:43:31 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/17 16:35:45 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_cmd	*ft_lstnew_cmd(void)
{
	t_cmd	*element;

	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->input = NULL;
	element->output = NULL;
	element->command = NULL;
	element->args = NULL;
	element->child_cmd = NULL;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}
