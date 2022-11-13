/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrncmp_lex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:48:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/13 22:38:21 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	*ft_lststrncmp_lex(t_lex **lst, char *to_find, int n)
{
	t_lex	*tmp;	

	tmp = *lst;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, to_find, n))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
