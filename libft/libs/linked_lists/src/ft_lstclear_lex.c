/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_lex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:28 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/08 19:00:51 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

void	ft_lstclear_lex(t_lex **lst)
{
	t_lex	*temp;

	if (lst)
	{
		temp = *lst;
		while (temp != NULL)
		{
			temp = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			*lst = temp;
		}
	}
}
