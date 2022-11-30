/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:22:34 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 23:04:52 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_lex	*lst_of_occurrences_loop(t_lex *to_find, t_lex *r_value)
{
	t_lex	*dir_file;
	t_lex	*tmp;

	dir_file = r_value;
	while (dir_file && to_find)
	{
		if (!aplly_star(to_find, *dir_file, 0, 0))
		{
			if (!dir_file->prev)
				r_value = r_value->next;
			tmp = dir_file->next;
			ft_lstdelone_lex(dir_file);
			dir_file = tmp;
		}
		else
		{
			if (ft_strchr(dir_file->str, '*')
				|| ft_strchr(dir_file->str, '\'')
				|| ft_strchr(dir_file->str, '\"'))
				dir_file->str = put_in_quotes(dir_file->str, -1, 0, 0);
			dir_file = dir_file->next;
		}
	}
	free_lexer_struct(&to_find);
	return (r_value);
}

static t_lex	*lst_of_occurrences(char *path, int *err, \
	t_lex *to_find, int dir_only)
{
	t_lex	*r_value;

	if (!to_find)
	{
		free(path);
		*err = -2;
		return (NULL);
	}
	r_value = send_dir_content(path, dir_only, err);
	free(path);
	if (!r_value)
	{
		ft_lstclear_lex(&to_find);
		return (NULL);
	}
	return (lst_of_occurrences_loop(to_find, r_value));
}

static void	add_path(char *path, t_lex *paths, int *index, int *index2)
{
	int	quotes;

	quotes = 0;
	while (paths->str[++(*index)] && (paths->str[(*index)] != '*' || quotes))
	{
		if (!(quotes) && is_there("\'\"", paths->str[(*index)]))
			quotes = paths->str[(*index)];
		else if (quotes == paths->str[(*index)])
			quotes = 0;
		else
			path[(*index2)++] = paths->str[(*index)];
	}
	if (paths->str[(*index)] == '*' && !quotes)
		path[(*index2)] = '*';
	*(path + ((*index2) + 1)) = '\0';
	if (path[(*index2)] != '*' || quotes)
		return ;
	while ((*index2) >= 0 && path[(*index2)] != '/')
		path[(*index2)--] = '\0';
	while ((*index) >= 0 && paths->str[(*index)] != '/')
		(*index)--;
	if ((*index) >= 0 && paths->str[(*index)] == '/')
		(*index)++;
	else
		(*index) = 0;
}

static int	add_el_to_var(char *path, char *to_find, t_lex *paths)
{
	int	index;
	int	index2;
	int	quotes;

	index = -1;
	index2 = 0;
	quotes = 0;
	add_path(path, paths, &index, &index2);
	if (!*path)
		*path = '.';
	if (index >= 0)
	{
		index2 = 0;
		quotes = is_in_quotes(paths->str, &paths->str[index]);
		if (quotes)
			to_find[index2++] = quotes;
		while (paths->str[index] && !is_there("/", paths->str[index]))
			to_find[index2++] = paths->str[index++];
		to_find[index2] = '\0';
	}
	return (index);
}

t_lex	*find_occurrences(t_lex *paths, int *err)
{
	int		index;
	char	*path;
	char	*to_find;
	t_lex	*to_find_lex;

	path = malloc((ft_strlen(paths->str) + 1) * sizeof(char));
	if (!path)
	{
		*err = -2;
		return (NULL);
	}
	to_find = malloc((ft_strlen(paths->str) + 1) * sizeof(char));
	if (!to_find)
	{
		*err = -2;
		return (NULL);
	}
	index = add_el_to_var(path, to_find, paths);
	to_find_lex = ft_lstsplit_charset_lex(to_find, "*\"\'");
	free(to_find);
	if (paths->str[index] && (paths->str[index] == '/') && to_find)
		return (lst_of_occurrences(path, err, to_find_lex, 1));
	else
		return (lst_of_occurrences(path, err, to_find_lex, 0));
}
