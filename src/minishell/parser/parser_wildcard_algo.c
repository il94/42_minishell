/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_algo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:50:11 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 23:09:55 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	verif_quotes(t_lex **to_find, int *quotes)
{
	if (!*quotes && *to_find && is_there("\'\"", (*to_find)->str[0]))
	{
		*quotes = (*to_find)->str[0];
		*to_find = (*to_find)->next;
		return (1);
	}
	else if (*quotes && *to_find && *quotes == (*to_find)->str[0])
	{
		*quotes = 0;
		*to_find = (*to_find)->next;
		return (1);
	}
	return (0);
}

static int	is_in_star(t_lex **to_find, int quotes, int *in_star, int *index)
{
	if (*to_find && !ft_strcmp((*to_find)->str, "*") && !quotes)
	{
		while (*to_find && !ft_strcmp((*to_find)->str, "*"))
			*to_find = (*to_find)->next;
		*in_star = 1;
		(*index)--;
		return (1);
	}
	return (0);
}

static int	next(int quotes, t_lex **tf)
{
	t_lex	*to_find;

	to_find = *tf;
	while (to_find)
	{
		if (!quotes && to_find && is_there("\'\"", (to_find)->str[0]))
			quotes = (to_find)->str[0];
		else if (quotes && to_find && quotes == (to_find)->str[0])
			quotes = 0;
		else
			return (1);
		to_find = to_find->next;
	}
	return (0);
}

static int	ended_by(char *name, char *str)
{
	int		i;
	int		j;

	if (!name || !str)
		return (0);
	i = ft_strlen(name) - 1;
	j = ft_strlen(str) - 1;
	if (j > i)
		return (0);
	while (j >= 0)
	{
		if (name[i--] != str[j--])
			return (0);
	}
	return (1);
}

int	aplly_star(t_lex *to_find, t_lex dir_file, int index, int in_star)
{
	int	quotes;

	quotes = 0;
	while (to_find)
	{
		if (index > (int)ft_strlen(dir_file.str))
			return (0);
		else if (verif_quotes(&to_find, &quotes))
			quotes = quotes;
		else if (to_find && !ft_strncmp(dir_file.str + index, \
			to_find->str, ft_strlen(to_find->str)))
		{
			if (!next(quotes, &to_find->next)
				&& !ended_by(dir_file.str, to_find->str))
				return (0);
			index += ft_strlen(to_find->str);
			to_find = to_find->next;
			in_star = 0;
		}
		else if (in_star || is_in_star(&to_find, quotes, &in_star, &index))
			index += 1;
		else if (!in_star)
			return (0);
	}
	return (1);
}
