/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrncmp_lex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:48:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/12 17:06:08 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	*ft_lststrncmp_lex(t_lex *lst, char *to_find, int n)
{
	while (lst)
	{
		if (!ft_strncmp(lst->str, to_find, n))
		{
			printf("trouve\n");
			return (lst);
		}
		lst = lst->next;
	}
	printf("pas trouve\n");
	return (NULL);
}
