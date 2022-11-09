/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__ft_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:11:41 by auzun             #+#    #+#             */
/*   Updated: 2022/11/08 14:01:12 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*cut_there(char *str, *index)
{
	char	*cuted;
	int		i;

	cuted = malloc((index + 1) * sizeof(char));
	if (!cuted)
		return (NULL);
	i = -1;
	while (++i < index)
		cuted[i] = str[i];
	cuted[i] = '\0';
	return (cuted);
}

t_lex	*split_str(t_data *data, char *str)
{
	t_lex	*lst;
	t_lex	*new;
	int		i;

	i = -1;
	lst = NULL;
	while (str[++i])
	{
		if (str[i] == ' ' && !is_in_quotes(str, &str[i]))
		{
			new = ft_lstnew_lex(cut_there(str, i));
			if (!new || new->str)
			{
				ft_lstclear_lex(lst);
				free(str);
				free_all_and_exit(data, "malloc");
			}
			ft_lstadd_back_lex(&lst, new);
		}
	}
	return (lst);
}

t_lex	*ft_expand(t_data *data, char *str)
{
	t_lex	*lst;
	char	*expanded;

	if (!is_there_el_outside_quotes(str, '$'))
		return (NULL);
	expanded = check_expand(data, str, 0, 0);
	free(str);
	lst = split_str(data, expanded);
	if (!lst)
	{
		lst = ft_lstnew_lex(expanded);
		if (!lst)
		{
			free(expand);
			free_all_and_exit(data, "malloc");
		}
	}
	return (lst);
}