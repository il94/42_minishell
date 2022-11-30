/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:34:48 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 19:15:58 by ilandols         ###   ########.fr       */
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

	if (*lexer && (is_there(QUOTES, (*lexer)->str[0]) || is_there(QUOTES,
				(*lexer)->str[ft_strlen((*lexer)->str) - 1])))
	{
		if ((*lexer)->prev && !is_there(TOKENS, (*lexer)->prev->str[0])
			&& !ft_iswhitespace((*lexer)->prev->str[0]))
			concat_element(lexer, TRUE);
		ft_strlcpy(quote, &(*lexer)->str[ft_strlen((*lexer)->str) - 1], 2);
		if (!ft_lststrncmp_lex(&(*lexer)->next, quote, 1))
			return (1);
		while (ft_strcmp((*lexer)->next->str, quote))
			concat_element(lexer, FALSE);
		concat_element(lexer, FALSE);
	}
	else if ((*lexer)->prev && !ft_iswhitespace((*lexer)->str[0])
		&& is_there(QUOTES,
			(*lexer)->prev->str[ft_strlen((*lexer)->prev->str) - 1]))
		concat_element(lexer, TRUE);
	return (1);
}

int	concat_tokens(t_lex **lexer)
{
	char	token[2];

	if (is_there(TOKENS, (*lexer)->str[0]))
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
		concat_quotes(lexer);
		if ((*lexer)->next && ft_isprint((*lexer)->next->str[0]))
		{
			(*lexer)->str = ft_strjoin_free((*lexer)->str, (*lexer)->next->str);
			if (!(*lexer)->str)
				return (0);
			ft_lstdelone_lex((*lexer)->next);
		}
		if ((*lexer)->prev && !ft_iswhitespace((*lexer)->prev->str[0]))
			concat_element(lexer, TRUE);
	}
	return (1);
}

int	concat_lexer(t_data *data)
{
	while (data->lexer)
	{
		if (!concat_env(&(data->lexer)) || !concat_quotes(&(data->lexer))
			|| !concat_tokens(&(data->lexer))
			|| !concat_ampersand(&(data->lexer)))
			free_all_and_exit(data, "malloc");
		if (g_exit_status > 0)
			return (0);
		data->lexer = (data->lexer)->next;
	}
	data->lexer = data->start_lex;
	if (search_closing_parenthese(data->lexer))
	{
		g_exit_status = 2;
		ft_printf_fd(2,
			"minishell: syntax error (minishell) invalid use of parentheses\n");
		return (0);
	}
	if (!search_closing_quote(data->lexer))
	{
		g_exit_status = 2;
		ft_printf_fd(2,
			"minishell: syntax error (minishell) invalid use of quotes\n");
	}
	return (1);
}
