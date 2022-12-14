/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:16:35 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 23:14:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		index2;
	int		quotes;
	char	*rvalue;
	char	*tmp;

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
	tmp = ft_strjoin(rvalue, &path[index2]);
	free(rvalue);
	return (tmp);
}

char	*concate_paths(char *path, char *finded)
{
	char	*rvalue;
	char	*new_path;

	new_path = malloc((ft_strlen(path) + 1) * sizeof(char));
	if (!new_path)
		return (NULL);
	rvalue = add_el_to_new_path(new_path, path, finded);
	if (!rvalue)
		return (NULL);
	return (rvalue);
}
