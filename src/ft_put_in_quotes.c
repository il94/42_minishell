/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_in_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:57:27 by auzun             #+#    #+#             */
/*   Updated: 2022/11/11 14:30:07 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	nb_spe_char(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (is_there("\'\"*", str[i]))
			count++;
	}
	return (count);
}

int	other_quote(char c)
{
	if (c == '\'')
		return ('\"');
	else
		return ('\'');
}

void	verif_quotes_closed(int quotes, int j, char *rvalue, char *name)
{
	if (quotes)
		rvalue[j++] = quotes;
	rvalue[j] = '\0';
	free(name);
}

char	*put_in_quotes(char *name, int i, int j, int quotes)
{
	char	*rvalue;

	rvalue = malloc((ft_strlen(name) + \
		(nb_spe_char(name) * 2) + 1) * sizeof(char));
	if (!rvalue)
		return (NULL);
	while (name[++i])
	{
		if (!quotes && is_there("\'\"*", name[i]))
		{
			quotes = other_quote(name[i]);
			rvalue[j++] = quotes;
			rvalue[j++] = name[i];
		}
		else if (name[i] == quotes)
		{
			rvalue[j++] = name[i--];
			quotes = 0;
		}
		else
			rvalue[j++] = name[i];
	}
	verif_quotes_closed(quotes, j, rvalue, name);
	return (rvalue);
}
