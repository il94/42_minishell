/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:16:35 by auzun             #+#    #+#             */
/*   Updated: 2022/11/06 23:08:56 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static char	*add_path(char *new_path, char *path, int *index2)
{
	int	index;
	int	quotes;

	quotes = 0;
	index = 0;
	while (path && path[(*index2)] && path[(*index2)] != '*')
		new_path[index++] = path[(*index2)++];
	new_path[index++] = path[(*index2)];
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
	return (new_path);
}

static char	*add_el_to_new_path(char *new_path, char *path, char *finded)
{
	int		index;
	int		index2;
	char	*rvalue;
	int		quotes;

	index = 0;
	index2 = 0;
	add_path(new_path, path, &index2);
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
		path[index2] = quotes;
		path[--index2] = '/';
	}
	rvalue = ft_strjoin(rvalue, &path[index2]);
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
