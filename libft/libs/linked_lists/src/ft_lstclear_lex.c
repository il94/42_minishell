/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_lex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:35:28 by ilyes             #+#    #+#             */
/*   Updated: 2022/10/18 16:37:47 by ilandols         ###   ########.fr       */
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
			free((*lst)->str);
			free(*lst);
			*lst = temp;
		}
	}
}
