/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:28 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/07 17:18:06 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

void	ft_lstclear(t_cmd **lst)
{
	t_cmd	*temp;

	temp = *lst;
	if (lst)
	{
		while (temp)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
	}
}
