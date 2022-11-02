/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:22:34 by auzun             #+#    #+#             */
/*   Updated: 2022/11/02 17:16:22 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	aplly_star(t_lex *to_find, t_lex dir_file, int index, int in_star)
{
	int	quotes;

	quotes = 0;
	while (to_find)
	{
		if (!quotes && is_there("\'\"", to_find->str[0]))
		{
			quotes = to_find->str[0];
			to_find = to_find->next;
		}
		if (quotes && quotes == to_find->str[0])
		{
			quotes = 0;
			to_find = to_find->next;
		}
		if (index >= ft_strlen(dir_file.str))
			return (0);
		if (!ft_strncmp(dir_file.str + index, \
			to_find->str, ft_strlen(to_find->str)))
		{
			if (!to_find->next && ft_strcmp(dir_file.str + index, to_find->str))
				return (0);
			index += ft_strlen(to_find->str);
			to_find = to_find->next;
			in_star = 0;
		}
		else if (!ft_strcmp(to_find->str, "*") && !quotes)
		{
			to_find = to_find->next;
			index += 1;
			in_star = 1;
		}
		else if (in_star)
			index += 1;
		else if (!in_star)
			return (0);
	}
	return (1);
}

static t_lex	*lst_of_occurrences_loop(t_lex *to_find, t_lex *r_value)
{
	t_lex	*dir_file;
	t_lex	*tmp;

	dir_file = r_value;
	while (dir_file)
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
			if (ft_strchr(dir_file->str, '*'))
			{
				dir_file->str = ft_strjoin(dir_file->str, "\'");
				dir_file->str = ft_strjoin("\'", dir_file->str);
			}
			dir_file = dir_file->next;
		}
	}
	return (r_value);
}

static t_lex	*lst_of_occurrences(char *path, int *err, \
	t_lex *to_find, int dir_only)
{
	t_lex	*r_value;
	t_lex	*dir_file;
	t_lex	*tmp;

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

static int	add_el_to_var(char *path, char *to_find, t_lex *paths)
{
	int	index;
	int	index2;
	int	quotes;

	index = -1;
	index2 = 0;
	quotes = 0;
	while (paths->str[++index] && (paths->str[index] != '*' || quotes))
	{
		if (!(quotes) && is_there("\'\"", paths->str[index]))
			quotes = paths->str[index];
		else if (quotes == paths->str[index])
			quotes = 0;
		else
			path[index2++] = paths->str[index];
	}
	if (paths->str[index] == '*' && !quotes)
		path[index2] = '*';
	*(path + (index2 + 1)) = '\0';
	if (path[index2] == '*' && !quotes)
	{
		while (index2 >= 0 && path[index2] != '/')
			path[index2--] = '\0';
		while (index >= 0 && paths->str[index] != '/')
			index--;
		if (index >= 0 && paths->str[index] == '/')
			index++;
		else
			index = 0;
		if (!*path)
			*path = '.';
	}
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
	printf("to find = %s and path = %s\n", to_find, path);
	return (index);
}

t_lex	*find_occurrences(t_lex *paths, int *err)
{
	int		index;
	char	*path;
	char	*to_find;

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
	if (paths->str[index] && (paths->str[index] == '/') && to_find)
		return (lst_of_occurrences(path, err, \
		ft_lstsplit_charset_lex(to_find, "*"), 1));
	else
		return (lst_of_occurrences(path, err, \
		ft_lstsplit_charset_lex(to_find, "\"\'*"), 0));
}
