/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:16:35 by auzun             #+#    #+#             */
/*   Updated: 2022/11/04 16:57:11 by auzun            ###   ########.fr       */
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
	char			*name;

	ls = NULL;
	/*if (!verif_dir(&d, &dir, path, err))
		return (NULL);*/
	if (!access(path, F_OK))
	{
		printf("WEWEWWEE NTMDSFSDALKFJDSALKFJDSL\n");
		exit(1);
	}
	else
	{
		printf("fdsafdas\n");
		exit(2);
	}
	while (dir)
	{
		if (!only_dir | (only_dir && dir->d_type == DT_DIR
				&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, "..")))
		{
			name = ft_strdup(dir->d_name);
			new = ft_lstnew_lex(name);
			if (!new || !new->str)
				return (exit_loop(d, &ls, err));
			ft_lstadd_back_lex(&ls, new);
		}
		dir = readdir(d);
	}
	closedir(d);
	return (ls);
}

/*static char	*add_el_to_new_path(char *new_path, char *path, char *finded)
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
}*/

static char	*add_el_to_new_path(char *new_path, char *path, char *finded)
{
	int		index;
	int		index2;
	char	*rvalue;
	int		quotes;

	index = 0;
	index2 = 0;
	while (path && path[index2] && path[index2] != '*')
		new_path[index++] = path[index2++];
	new_path[index++] = path[index2];
	new_path[index--] = '\0';
	if (new_path[index] == '*')
	{
		while (index >= 0 && new_path[index] != '/')
			new_path[index--] = '\0';
		quotes = is_in_quotes(new_path, &new_path[index]);
		if (index >= 0 && quotes)
		{
			new_path[index++] = quotes;
			new_path[index] = '/';
			quotes = 0;
		}
	}
	rvalue = ft_strjoin(new_path, finded);
	free(new_path);
	if (!rvalue)
		return (NULL);
	while (path[index2] && path[index2] != '/')
		index2++;
	if (!path[index2])
		return (rvalue);
	quotes = is_in_quotes(path, &path[index2]);
	if (quotes)
	{
		printf("salut\n\nsalusdafjsd\n\n");
		path[index2] = quotes;
		path[--index2] = '/'; 
	}
	rvalue = ft_strjoin(rvalue, &path[index2]);
	printf("%s\n", rvalue);
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
