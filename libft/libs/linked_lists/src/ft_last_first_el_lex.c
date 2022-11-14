/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_first_el_lex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:00:36 by auzun             #+#    #+#             */
/*   Updated: 2022/11/14 02:01:14 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	**first_el(t_lex **lst)
{
	if (*lst && (*lst)->prev)
		return (first_el(&(*lst)->prev));
	return (lst);
}

t_lex	**last_el(t_lex **lst)
{
	if (*lst && (*lst)->next)
		return (last_el(&(*lst)->next));
	return (lst);
}
