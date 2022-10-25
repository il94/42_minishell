/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:36 by auzun             #+#    #+#             */
/*   Updated: 2022/10/25 23:18:08 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include "../include/minishell.h"


void	dell_occur_in_lst(t_lex **head_lst, t_lex **head_paths, t_lex **paths)
{
	t_lex	*tmp;

	if (*head_lst)
	{
		if ((*head_paths) == (*paths))
			(*head_paths) = (*head_paths)->next;
		tmp = (*paths)->next;
		ft_lstdelone_lex((*paths));
		(*paths) = tmp;
		tmp = NULL;
		ft_lstclear_lex(head_lst);
		head_lst = NULL;
	}
	else if (!(*head_lst) && ft_strchr((*paths)->str, '*'))
	{
		if ((*head_paths) == (*paths))
			(*head_paths) = (*head_paths)->next;
		tmp = (*paths)->next;
		ft_lstdelone_lex((*paths));
		(*paths) = tmp;
		tmp = NULL;
	}
}

int	add_occur_to_list(int *err, t_lex **head_lst, t_lex **head_paths, t_lex **paths)
{
	t_lex	*lst;
	t_lex	*new;
	char	*str;

	lst = *head_lst;
	while (lst)
	{
		str = concate_paths((*paths)->str, lst->str);
		if (!str)
			return (0);
		new = ft_lstnew_lex(str);
		if (!new)
			return (0);
		ft_lstadd_back_lex(paths, new);
		lst = lst->next;
	}
	dell_occur_in_lst(head_lst, head_paths, paths);
	return (1);
}

void	clear_wildi(t_data *data, t_lex *head_paths, t_lex *head_lst, int exit)
{
	if (head_paths)
		free_lexer_struct(&head_paths);
	if (head_lst)
		free_lexer_struct(&head_lst);
	if (exit)
		free_all_and_exit(data, "malloc");
}

t_lex	*wildiwonkard(t_data *data, char *path)
{
	int		err;
	t_lex	*head_paths;
	t_lex	*head_lst;
	t_lex	*paths;

	err = 1;
	head_lst = NULL;
	if (!ft_strchr(path, '*'))
		return (NULL);
	paths = ft_lstnew_lex(ft_strdup(path));
	head_paths = paths;
	while (paths)
	{
		if (ft_strchr(paths->str, '*'))
			head_lst = find_occurrences(paths, &err);
		if (err == -2 || !add_occur_to_list(&err, &head_lst, &head_paths, &paths))
			clear_wildi(data, head_paths, head_lst, 1);
		else if (err == -1)
				printf("nothing\n");
		else if (err == 0)
			printf("invalid path\n");
		if (paths && !ft_strchr(paths->str, '*'))
			paths = paths->next;
	}
	if (head_paths == NULL)
		printf("no occurr sorry!\n");
	return (head_paths);
}
