/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/11 22:34:23 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*char	*find_file(t_lex **lst, t_redi r)
{
	if (r == L_CHEVRON || r == R_CHEVRON || r == R_DOUBLE_CHEVRON)
	
}

int		find_redi_info(t_lex **lst, t_cmd *cmd)
{
	int	redi;

	
	redi = define_redi(lst);
	if (redi == L_CHEVRON
		|| redi == L_DOUBLE_CHEVRON)
	{
		commands->input->operator = redi;
		command->input->file
	}
	else if (redi == R_CHEVRON
		|| redi == R_DOUBLE_CHEVRON)
	{
		commands->output->operator = redi;
		command->output->file
	}
	if (commands->input->operator == L_DOUBLE_CHEVRON
		|| commands->input->operator == R_DOUBLE_CHEVRON)
		lst = lst->next;
	else if (define_file(lst))
	{
	
	}
}*/

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
	/*while (lst)
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
	}*/
	ft_lstclear_lex(&lst);
}
