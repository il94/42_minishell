/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:13:01 by auzun             #+#    #+#             */
/*   Updated: 2022/10/17 20:12:58 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_fd	*ft_lstnew_fd(void)
{
	t_fd	*element;

	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->fd = -1;
	element->file = NULL;
	element->operator = NOTHING_R;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}
