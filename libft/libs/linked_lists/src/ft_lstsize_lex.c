/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_lex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:35:09 by ilyes             #+#    #+#             */
/*   Updated: 2022/11/25 18:31:50 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

int	ft_lstsize_lex(t_lex *lst)
{
	t_lex	*lex;
	int		i;

	lex = lst;
	i = 0;
	while (lex)
	{
		lex = lex->next;
		i++;
	}
	return (i);
}
