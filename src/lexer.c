/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/13 16:55:57 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	define_delimiter(t_data *data)
{
	data->commands->delimiter = get_delimiter(data->lexer);
	if (data->commands->delimiter)
	{
		ft_lstadd_back_cmd(&data->commands, ft_lstnew_cmd());
		if (!data->commands->next)
			free_all_and_exit(data, "malloc");
		if (data->commands->delimiter == AND || data->commands->delimiter == OR)
			data->lexer = data->lexer->next;
		data->commands = data->commands->next;
	}
}

int	concat_quotes(t_lex **lex, char *quote)
{

	printf("elem = %s\n", (*lex)->content);

	while ((*lex) && (*lex)->next && ft_strcmp((*lex)->next->content, quote))
	{
		(*lex)->content = ft_strjoin_free((*lex)->content, (*lex)->next->content);
		if (!(*lex)->content)
			return (0);
		ft_lstdelone_lex((*lex)->next);
	}
	if (!(*lex))
		return (0);
	(*lex)->content = ft_strjoin_free((*lex)->content, (*lex)->next->content);
	if (!(*lex)->content)
		return (0);
	ft_lstdelone_lex((*lex)->next);
	// if ((*lex)->next)
	// 	(*lex) = (*lex)->next;
	return (1);
}

void	concat_lexer(t_lex **lexer)
{
	t_lex *temp;

	temp = *lexer;
	while (*lexer)
	{
		if (!ft_strcmp((*lexer)->content, "\'"))
			concat_quotes(lexer, "\'");
		if (!ft_strcmp((*lexer)->content, "\""))
			concat_quotes(lexer, "\"");
		*lexer = (*lexer)->next;
	}
	*lexer = temp;
}

void	lexer(t_data *data)
{
	t_cmd	*start_cmd;
	t_lex	*start_lex;

	data->lexer = NULL;
	data->lexer = ft_lstsplit_charset_lex(data->prompt, "><&|() \t$\'\"");
	if (!data->lexer)
		return ;
	ft_lstprint_lex(data->lexer);
	printf("========\n");
	concat_lexer(&(data->lexer));
	ft_lstprint_lex(data->lexer);
	data->commands = ft_lstnew_cmd();
	if (!data->commands)
		free_all_and_exit(data, "malloc"); // ne pas oublier le free de str readline
	start_cmd = data->commands;
	start_lex = data->lexer;
	while (data->lexer)
	{
		if (is_token(data->lexer, "&", "&"))
		{
			printf("ERROR\n"); // afficher le bon message
			break ;
		}
		define_delimiter(data);
		/* A effectuer dans define files ou redi */
		// if ((data->data->commands)->delimiter == PIPE_D)
		// 	(data->data->commands)->next->input->operator = PIPE_R;
		data->lexer = data->lexer->next;
	}
	data->lexer = start_lex;
	free_lexer_struct(&(data->lexer));
}
