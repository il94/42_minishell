/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstis_correct_lex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:20:58 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/08 18:37:26 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/linked_lists.h"

int	ft_lstis_correct_lex(t_lex *lst, int size)
{
	return (ft_lstsize_lex(lst) == size);
}
