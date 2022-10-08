/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:28 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/08 18:08:50 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*temp;

	if (lst)
	{
		temp = *lst;
		while (temp != NULL)
		{
			temp = (*lst)->next;
			free(*lst);
			*lst = temp;
		}
	}
}
