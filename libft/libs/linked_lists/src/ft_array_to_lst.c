/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:02:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 18:21:48 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_list	*ft_array_to_lst(char **array)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = NULL;
	while (array[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(array[i]));
		i++;
	}
	return (lst);
}
