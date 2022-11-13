/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrncmp_lex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:48:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/13 18:01:16 by ilandols         ###   ########.fr       */
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
		{
			printf("OK = %p\n", tmp);
			return (tmp);
		}
		tmp = tmp->next;
	}
	printf("KO = %p\n", tmp);
	return (NULL);
}
