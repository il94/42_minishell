/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:34:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/20 18:08:18 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_closing_quote(t_lex *lexer, char *quote)
{
	while (lexer)
	{
		if (!ft_strcmp(lexer->str, quote))
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int	search_closing_parenthese(t_lex *lexer)
{
	int		opened;
	int		closed;

	opened = 0;
	closed = 0;
	while (lexer)
	{
		if (lexer->str[0] == '(')
			opened++;
		if (lexer->str[0] == ')')
			closed++;
		if (closed > opened)
			return (0);
		lexer = lexer->next;
	}
	return (closed == opened);
}

int	concat_quotes(t_lex **lexer)
{
	char	quote[2];

	ft_strlcpy(quote, (*lexer)->str, 2);
	if (!search_closing_quote((*lexer)->next, quote))
	{
		printf("ERROR\n");
		return (0);
	}
	while (ft_strcmp((*lexer)->next->str, quote))
	{
		(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
		if (!(*lexer)->str)
			return (-1);
		ft_lstdelone_lex((*lexer)->next);
	}
	(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
	if (!(*lexer)->str)
		return (-1);
	ft_lstdelone_lex((*lexer)->next);
	return (1);
}

int	concat_tokens(t_lex **lexer)
{
	char	token[2];

	ft_strlcpy(token, (*lexer)->str, 2);
	if ((*lexer)->next && !ft_strcmp((*lexer)->next->str, token))
	{
		(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
		if (!(*lexer)->str)
			return (-1);
		ft_lstdelone_lex((*lexer)->next);
	}
	return (1);
}

int	concat_env_variable(t_lex **lexer)
{
	if ((*lexer)->next && ft_isprint((*lexer)->next->str[0]))
	{
		(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
		if (!(*lexer)->str)
			return (-1);
		ft_lstdelone_lex((*lexer)->next);
	}
	return (1);
}

int	concat_lexer(t_data *data)
{
	int		return_value;

	if (!search_closing_parenthese(data->lexer))
	{
		printf("ERROR\n");
		return (0);
	}
	while (data->lexer)
	{
		if (!ft_strcmp(data->lexer->str, "\'")
			|| !ft_strcmp(data->lexer->str, "\""))
		{
			return_value = concat_quotes(&(data->lexer));
			if (return_value == -1)
				free_all_and_exit(data, "malloc");
			else if (return_value == 0)
				return (0);
		}
		else if (!ft_strcmp(data->lexer->str, "&")
			||!ft_strcmp(data->lexer->str, "|")
			||!ft_strcmp(data->lexer->str, "<")
			||!ft_strcmp(data->lexer->str, ">"))
		{
			return_value = concat_tokens(&(data->lexer));
			if (return_value == -1)
				free_all_and_exit(data, "malloc");
			else if (return_value == 0)
				return (0);
		}
		else if (!ft_strcmp(data->lexer->str, "$"))
		{
			return_value = concat_env_variable(&(data->lexer));
			if (return_value == -1)
				free_all_and_exit(data, "malloc");
			else if (return_value == 0)
				return (0);
		}
		data->lexer = (data->lexer)->next;
	}
	return (1);
}
