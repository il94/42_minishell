/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:43:31 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/07 17:20:48 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_cmd	*ft_lstnew(void)
{
	t_cmd	*element;

	element = malloc(sizeof(*element));
	if (element == NULL)
		return (NULL);
	element->input = NULL;
	element->output = NULL;
	element->command = NULL;
	element->args = NULL;
	element->child_cmd = NULL;
	element->next = NULL;
	return (element);
}
