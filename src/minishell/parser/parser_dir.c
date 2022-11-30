/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:08:35 by auzun             #+#    #+#             */
/*   Updated: 2022/11/21 16:47:36 by ilandols         ###   ########.fr       */
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
	if (!verif_dir(&d, &dir, path, err))
		return (NULL);
	while (dir)
	{
		if ((!only_dir || (only_dir && dir->d_type == DT_DIR))
			&& ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			name = ft_strdup(dir->d_name);
			new = ft_lstnew_lex_dup(name);
			if (!new || !new->str)
				return (exit_loop(d, &ls, err));
			ft_lstadd_back_lex(&ls, new);
		}
		dir = readdir(d);
	}
	closedir(d);
	return (ls);
}
