/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ft_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:11:41 by auzun             #+#    #+#             */
/*   Updated: 2022/12/04 19:00:36 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cut_there(char *str, int start, int end)
{
	char	*cuted;
	int		i;

	if (!str || !str[start] || !str[end])
		return (NULL);
	cuted = malloc(((end + 2)) * sizeof(char));
	if (!cuted)
		return (NULL);
	i = 0;
	while (&str[start + i] <= &str[end])
	{
		cuted[i] = str[start + i];
		i++;
	}
	cuted[i] = '\0';
	return (cuted);
}

t_lex	*create_new_el(char *str, int *start, int *end)
{
	t_lex	*new;

	new = NULL;
	if ((!str[(*end) + 1]
			|| (str[*end] == ' ')) && !is_in_quotes(str, &str[*end]))
	{
		if ((str[*end] == ' ') && !is_in_quotes(str, &str[*end]))
			new = ft_lstnew_lex_dup(cut_there(str, *start, (*end) - 1));
		else
			new = ft_lstnew_lex_dup(cut_there(str, *start, *end));
		while (str[(*end) + 1] && str[(*end) + 1] == ' ')
			(*end)++;
		*start = (*end) + 1;
	}
	return (new);
}

void	add_new_el_to_lst(t_data *data, t_lex **new, t_lex **lst, char *str)
{
	if (!(*new) || !(*new)->str)
	{
		free(str);
		ft_lstclear_lex(lst);
		free_all_and_exit(data, "malloc");
	}
	ft_lstadd_back_lex(lst, *new);
}

t_lex	*split_str(t_data *data, char *str)
{
	t_lex	*lst;
	t_lex	*new;
	int		start;
	int		end;

	end = 0;
	while (str[end] && str[end] == ' ')
		end++;
	start = end;
	lst = NULL;
	new = NULL;
	while (str[end])
	{
		if ((!str[end + 1]
				|| (str[end] == ' ')) && !is_in_quotes(str, &str[end]))
		{
			new = create_new_el(str, &start, &end);
			add_new_el_to_lst(data, &new, &lst, str);
		}
		end++;
	}
	return (lst);
}

t_lex	*ft_expand(t_data *data, char *str)
{
	t_lex	*lst;
	char	*expanded;
	char	*dup_str;

	if (!str || !ft_strchr(str, '$'))
		return (NULL);
	dup_str = ft_strdup(str);
	if (!dup_str)
		free_all_and_exit(data, "malloc");
	expanded = check_expand(data, &dup_str, 0, 0);
	if (dup_str)
		free(dup_str);
	lst = split_str(data, expanded);
	if (!lst)
	{
		lst = ft_lstnew_lex_dup(ft_strdup(expanded));
		if (!lst || !lst->str)
		{
			free(expanded);
			free_all_and_exit(data, "malloc");
		}
	}
	if (expanded)
		free(expanded);
	return (lst);
}
