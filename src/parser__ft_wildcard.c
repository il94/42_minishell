/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__ft_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:34:12 by auzun             #+#    #+#             */
/*   Updated: 2022/11/08 12:49:52 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	take_off_quotes_in_lst(t_data *data, t_lex **lst, char *path)
{
	t_lex	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '\'') || ft_strchr(tmp->str, '\"'))
			tmp->str = take_off_quotes(tmp->str);
		if (!tmp->str)
		{
			free(path);
			free_lexer_struct(lst);
			free_all_and_exit(data, "malloc");
		}
		tmp = tmp->next;
	}
}

static void	take_off_invalid_matches(t_lex **h_matches)
{
	t_lex	*matches;
	t_lex	*tmp;

	matches = *h_matches;
	while (matches)
	{
		if (access(matches->str, F_OK))
		{
			if (matches == *h_matches)
				*h_matches = (*h_matches)->next;
			tmp = matches->next;
			ft_lstdelone_lex(matches);
			matches = tmp;
		}
		else
			matches = matches->next;
	}
}

t_lex	*ft_wildcard(t_data *data, char *path)
{
	t_lex	*matches;
	t_lex	*tmp;

	matches = wildiwonkard(data, path);
	if (!matches)
		return (NULL);
	take_off_quotes_in_lst(data, &matches, path);
	take_off_invalid_matches(&matches);
	return (matches);
}