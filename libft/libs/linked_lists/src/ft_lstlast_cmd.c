/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:57:18 by ilyes             #+#    #+#             */
/*   Updated: 2022/12/04 16:40:24 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	t_cmd	*temp;

	if (lst)
	{
		temp = lst;
		while (temp->next)
			temp = temp->next;
		return (temp);
	}
	else
		return (lst);
}
