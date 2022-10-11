/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/11 16:41:00 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer(t_cmd *commands, char *input)
{
	t_cmd	*start;
	t_lex	*lst;

	lst = NULL;
	lst = ft_lstsplit_charset_lex(input, "><&|() \t$\'\"");
	if (!lst)
		return ;


		
	commands = ft_lstnew_cmd();
	start = commands;
	while (lst)
	{
		if (define_delimiter(lst))
		{
			commands->delimiter = define_delimiter(lst);
			if (commands->delimiter == AND || commands->delimiter == OR)
				lst = lst->next;
			ft_lstadd_back_cmd(&lst, ft_lstnew_cmd());
			if (commands->delimiter == PIPE_D)
				commands->next->input->operator = PIPE_R;
			commands = commands->next;
			// child_cmd
		}
		else if (define_redi(lst))
		{
			if (define_redi(lst) == L_CHEVRON
				|| define_redi(lst) == L_DOUBLE_CHEVRON)
			{
				
			}
			else if (define_redi(lst) == R_CHEVRON
				|| define_redi(lst) == R_DOUBLE_CHEVRON)
			{
				
			}
			commands->input->operator = define_redi(lst);
			if (commands->input->operator == L_DOUBLE_CHEVRON
				|| commands->input->operator == R_DOUBLE_CHEVRON)
				lst = lst->next;
			else if (define_file(lst))
			{
			
			}
		}
		else if (define_command(lst))
		{
			
		}
		else if (define_args(lst))
		{
			
		}
		lst = lst->next;
	}
	ft_lstclear_lex(&lst);
}
