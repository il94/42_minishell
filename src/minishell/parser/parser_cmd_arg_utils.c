/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_arg_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:54:01 by auzun             #+#    #+#             */
/*   Updated: 2022/12/02 21:58:33 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lex	*switch_cmd_w_head_arg(t_data *data, t_cmd *command, t_lex *lst)
{
	t_lex	*args;

	free_lexer_struct(&lst);
	command->command = NULL;
	if (!command->args)
		return (NULL);
	command->command = ft_strdup(command->args->str);
	if (!command->command)
		free_all_and_exit(data, "malloc");
	args = command->args->next;
	ft_lstdelone_lex(command->args);
	command->args = args;
	return (parsing_cmd(data, command, command->command));
}

void	switch_head_arg_w_next_arg(t_lex **el, t_lex **cur, t_lex **args)
{
	t_lex	*tmp;

	free_lexer_struct(el);
	tmp = *args;
	if (*args == *cur)
	{
		tmp = (*args)->next;
		ft_lstdelone_lex(*args);
		*args = tmp;
		*cur = *args;
	}
	else
	{
		tmp = (*cur)->next;
		ft_lstdelone_lex(*cur);
		*cur = tmp;
	}
}
