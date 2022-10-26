/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:16:35 by auzun             #+#    #+#             */
/*   Updated: 2022/10/26 14:31:12 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	verif_dir(DIR **d, struct dirent **dir, char *path, int	*err)
{
	*d = opendir(path);
	if (*d == NULL)
	{
		*err = 0;
		return (0);
	}
	*dir = readdir(*d);
	if (!*dir)
	{
		*err = -1;
		return (0);
	}
	return (1);
}

static void	*exit_loop(DIR *d, t_lex **ls, int *err)
{
	closedir(d);
	free_lexer_struct(ls);
	*err = -2;
	return (NULL);
}

t_lex	*send_dir_content(char *path, int only_dir, int *err)
{
	t_lex			*ls;
	t_lex			*new;
	DIR				*d;
	struct dirent	*dir;

	ls = NULL;
	if (!verif_dir(&d, &dir, path, err))
		return (NULL);
	while (dir)
	{
		if (!only_dir | (only_dir && dir->d_type == DT_DIR
				&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, "..")))
		{
			new = ft_lstnew_lex(ft_strdup(dir->d_name));
			if (!new || !new->str)
				return (exit_loop(d, &ls, err));
			ft_lstadd_back_lex(&ls, new);
		}
		dir = readdir(d);
	}
	closedir(d);
	return (ls);
}

static char	*add_el_to_new_path(char *new_path, char *path, char *finded)
{
	int		index;
	char	*rvalue;

	index = 0;
	while (path && *path && *path != '*')
		new_path[index++] = *(path++);
	new_path[index++] = *path;
	new_path[index--] = '\0';
	if (new_path[index] == '*')
	{
		while (index >= 0 && new_path[index] != '/')
			new_path[index--] = '\0';
	}
	rvalue = ft_strjoin(new_path, finded);
	free(new_path);
	if (!rvalue)
		return (NULL);
	while (*path && *path != '/')
		path++;
	if (!path)
		return (rvalue);
	rvalue = ft_strjoin(rvalue, path);
	return (rvalue);
}

char	*concate_paths(char *path, char *finded)
{
	int		index;
	char	*rvalue;
	char	*new_path;

	index = 0;
	new_path = malloc((ft_strlen(path) + 1) * sizeof(char));
	if (!new_path)
		return (NULL);
	rvalue = add_el_to_new_path(new_path, path, finded);
	if (!rvalue)
		return (NULL);
	return (rvalue);
}
