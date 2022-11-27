/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_lex_to_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:13:01 by auzun             #+#    #+#             */
/*   Updated: 2022/11/25 22:57:12 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

static char	**add_el_to_array(t_lex *lst, char **array, int size)
{
	int	i;

	i = 0;
	while (i < size && lst)
	{
		if (lst->str)
		{
			array[i] = ft_strdup(lst->str);
			if (!array[i++])
			{
				ft_free_array(array);
				return (NULL);
			}
		}
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_lst_lex_to_array(t_lex *lst_lex)
{
	char	**array;
	t_lex	*lst;
	int		size;

	if (!lst_lex)
		return (NULL);
	size = ft_lstsize_lex(lst_lex);
	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	lst = lst_lex;
	array = add_el_to_array(lst, array, size);
	return (array);
}

