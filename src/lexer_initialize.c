/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:34:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/26 17:58:21 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	concat_ampersand(t_lex **lexer)
{
	if (!ft_strcmp((*lexer)->str, "&"))
	{
		if ((*lexer)->next && (!is_there("<>|()", (*lexer)->next->str[0])
				&& !ft_iswhitespace((*lexer)->next->str[0])
				&& ft_strcmp((*lexer)->next->str, "&&")))
		{
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
		if ((*lexer)->prev && (!is_there("<>|()", (*lexer)->prev->str[0])
				&& !ft_iswhitespace((*lexer)->prev->str[0])
				&& ft_strcmp((*lexer)->prev->str, "&&")))
		{
			*lexer = (*lexer)->prev;
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
	}
	return (1);
}

int	concat_quotes(t_lex **lexer)
{
	char	quote[2];

	if (!ft_strcmp((*lexer)->str, "\'")
		|| !ft_strcmp((*lexer)->str, "\""))
	{
		ft_strlcpy(quote, (*lexer)->str, 2);
		if (!search_closing_quote((*lexer)->next, quote))
		{
			g_exit_status = 2;
			printf("ERROR\n");
			return (1);
		}
		while (ft_strcmp((*lexer)->next->str, quote))
		{
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
		(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
		if (!(*lexer)->str)
			return (0);
		ft_lstdelone_lex((*lexer)->next);
	}
	return (1);
}

int	concat_tokens(t_lex **lexer)
{
	char	token[2];

	if (!ft_strcmp((*lexer)->str, "&")
		||!ft_strcmp((*lexer)->str, "|")
		||!ft_strcmp((*lexer)->str, "<")
		||!ft_strcmp((*lexer)->str, ">"))
	{
		ft_strlcpy(token, (*lexer)->str, 2);
		if ((*lexer)->next && !ft_strcmp((*lexer)->next->str, token))
		{
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
	}
	return (1);
}

int	concat_env(t_lex **lexer)
{
	if (!ft_strcmp((*lexer)->str, "$"))
	{
		if ((*lexer)->next && ft_isprint((*lexer)->next->str[0]))
		{
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
	}
	return (1);
}

int	concat_lexer(t_data *data)
{
	int		return_value;

	return_value = 1;
	if (!search_closing_parenthese(data->lexer))
	{
		// g_exit_status = ?;
		printf("ERROR\n");
		return (0);
	}
	while (data->lexer)
	{
		if (!concat_quotes(&(data->lexer)) || !concat_tokens(&(data->lexer))
			|| !concat_env(&(data->lexer)) || !concat_ampersand(&(data->lexer)))
			free_all_and_exit(data, "malloc");
		if (g_exit_status > 0)
			return (0);
		data->lexer = (data->lexer)->next;
	}
	data->lexer = data->start_lex;
	return (1);
}
