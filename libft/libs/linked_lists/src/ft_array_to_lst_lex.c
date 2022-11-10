/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_lst_lex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:02:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/10 15:58:27 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	*ft_array_to_lst_lex(char **array)
{
	t_lex	*lst;
	t_lex	*new;
	int		i;

	i = 0;
	lst = NULL;
	while (array && array[i])
	{
		new = ft_lstnew_lex(ft_strdup(array[i]));
		if (!new || !new->str)
		{
			ft_lstclear_lex(&lst);
			return (NULL);
		}
		ft_lstadd_back_lex(&lst, new);
		i++;
	}
	return (lst);
}
