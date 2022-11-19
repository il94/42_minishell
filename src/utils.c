/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:32:14 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/19 13:20:59 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_deli_char(t_deli r)
{
	if (r == PIPE_D)
		return ("|");
	else if (r == AND)
		return ("&&");
	else if (r == OR)
		return ("||");
	else
		return (NULL);
}

void	define_exit_status(char *to_print, int error_code)
{
	if (to_print)
		printf("%s", to_print);
	g_exit_status = error_code;
}

int	is_there(char *str, char in)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in == str[i])
			return (str[i]);
		i++;
	}
	return (0);
}

int	is_there_v2(char *is, char *there)
{
	int	i;

	if (!there)
		return (0);
	i = 0;
	while (there[i])
	{
		if (is_there(is, there[i]))
			return (there[i]);
		i++;
	}
	return (0);
}

int	is_in_quotes(char *start, char *now)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (start[++i] && &start[i] != now)
	{
		if (!quotes && is_there("\"\'", start[i]))
			quotes = start[i];
		else if (quotes && quotes == start[i])
			quotes = 0;
	}
	return (quotes);
}

int	is_there_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' && !is_in_quotes(str, &str[i]))
			return (1);
	}
	return (0);
}

int	is_there_el_outside_quotes(char *str, char el)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == el && !is_in_quotes(str, &str[i]))
			return (1);
	}
	return (0);
}

int	is_there_el_outside_quotes_v2(char *str, char *el)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (el[i])
	{
		if (is_there_el_outside_quotes(str, el[i]))
			return (1);
		i++;
	}
	return (0);
}

// t_lex	*add_lst_to_lst(t_lex *lst, t_lex *to_add)
// {
	
// }
