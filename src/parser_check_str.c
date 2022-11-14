/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:05 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:17 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*expand :
	si entre double quotes on va chercher la variable dans env
	si entre simple quotes on fait rien
	*/

static t_lex	*put_lst_in_lst(t_lex **new, t_lex **curr, int is_last)
{
	t_lex	*new_lst;

	new_lst = *curr;
	if (is_last)
	{
		(*last_el(&new_lst))->next = *first_el(new);
		(*first_el(new))->prev = (*last_el(&new_lst))->next;
		return (*(first_el(&new_lst)));
	}
	if (new_lst->prev)
	{
		new_lst->prev->next = *first_el(new);
		new_lst->prev->next->prev = new_lst->prev;
	}
	new_lst->prev = *last_el(new);
	new_lst->prev->next = new_lst;
	return (*(first_el(&new_lst)));
}

static void	add_matches_to_lst(t_lex **lst, t_lex **matches, t_lex **lst_str)
{
	t_lex	*tmp;
	int		is_last;

	tmp = *lst;
	is_last = 0;
	if (!(*lst)->next)
	{
		tmp = (*lst)->prev;
		ft_lstdelone_lex((*lst));
		is_last = 1;
	}
	else
	{
		tmp = (*lst)->next;
		ft_lstdelone_lex(*lst);
	}
	if (!(*lst) || !tmp)
	{
		*lst = NULL;
		*lst_str = *matches;
		return ;
	}
	(*lst) = tmp;
	*lst_str = put_lst_in_lst(matches, lst, is_last);
}

static t_lex	*check_wildcard(t_data *data, t_lex *lst_str)
{
	t_lex	*lst;
	t_lex	*path;
	t_lex	*path_lst;

	lst = lst_str;
	while (lst)
	{
		if (ft_strchr(lst->str, '*'))
		{
			path = ft_lstnew_lex_dup(ft_strdup(lst->str));
			if (!path || !path->str)
			{
				ft_lstclear_lex(&lst_str);
				free_all_and_exit(data, "malloc");
			}
			path_lst = ft_wildcard(data, path, lst_str);
			if (path_lst)
				add_matches_to_lst(&lst, &path_lst, &lst_str);
			else
				lst = lst->next;
		}
		else
			lst = lst->next;
	}
	return (lst_str);
}

static t_lex	*take_off_quotes_in_lst(t_data *data, t_lex *lst)
{
	t_lex	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp && tmp->str && ft_strchr(tmp->str, '\'')
			|| ft_strchr(tmp->str, '\"') && !ft_strchr(tmp->str, '*'))
		{
			tmp->str = take_off_quotes(tmp->str);
			if (!tmp->str)
			{
				free_lexer_struct(&lst);
				free_all_and_exit(data, "malloc");
			}
		}
		tmp = tmp->next;
	}
	return (lst);
}

t_lex	*check_str(t_data *data, char *str)
{
	t_lex	*lst_str;

	if (!str)
		return (NULL);
	lst_str = NULL;
	lst_str = ft_expand(data, str);
	/*lst_str = ft_lstsplit_charset_lex("*e", " "); test...*/
	if (!lst_str)
	{
		lst_str = split_str(data, str);
		if (lst_str)
			free(str);
	}
	if (!lst_str && str)
	{
		lst_str = ft_lstnew_lex_dup(ft_strdup(str));
		free(str);
		if (!lst_str || !lst_str->str)
			free_all_and_exit(data, "malloc");
	}
	lst_str = take_off_quotes_in_lst(data, lst_str);
	lst_str = check_wildcard(data, lst_str);
	return (lst_str);
}

/*
void	parser(t_data *data)
{
	return ;
}*/