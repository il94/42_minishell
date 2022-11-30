/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:32:14 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 17:25:59 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_deli_char(t_deli r)
{
	if (r == PIPE_D)
		return ("|");
	else if (r == AND)
		return ("&&");
	else if (r == OR)
		return ("||");
	else
		return (NULL);
}

int	is_in_quotes(char *start, char *now)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (start[++i] && &start[i] != now)
	{
		if (!quotes && is_there("\"\'", start[i]))
			quotes = start[i];
		else if (quotes && quotes == start[i])
			quotes = 0;
	}
	return (quotes);
}

int	is_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
