/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/10 16:46:47 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer(t_cmd *commands, char *input)
{
	t_lex	*lst;

	lst = NULL;
	lst = ft_lstsplit_charset_lex(input, "><&|() \t$\'\"");
	if (!lst)
		return ;
	ft_lstprint_lex(lst);
	ft_lstclear_lex(&lst);
}
