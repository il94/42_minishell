/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrrncmp_lex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:48:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 23:23:20 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

t_lex	*ft_lststrrncmp_lex(t_lex **lst, char *to_find)
{
	t_lex	*tmp;	
	char	*to_find_cut;

	tmp = *lst;
	while (tmp)
	{
		to_find_cut = ft_strcut_right(tmp->str, '=');
		if (!to_find_cut)
			exit (456);
		if (!ft_strrncmp(to_find, to_find_cut, ft_strlen(to_find_cut)))
		{
			free(to_find_cut);
			return (tmp);
		}
		tmp = tmp->next;
		free(to_find_cut);
	}
	return (NULL);
}
