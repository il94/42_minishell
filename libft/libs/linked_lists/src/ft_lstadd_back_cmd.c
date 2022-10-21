/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 03:03:59 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/14 13:24:27 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
	}
	else
		*lst = new;
}
