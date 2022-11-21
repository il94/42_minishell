/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_off_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:40:50 by auzun             #+#    #+#             */
/*   Updated: 2022/11/21 16:43:19 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*put_str_without_quotes(char *str, char *quoteless)
{
	int	quotes;
	int	i;
	int	j;

	quotes = 0;
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (!quotes && is_there("\'\"", str[i]))
			quotes = str[i];
		else if (quotes && quotes == str[i])
			quotes = 0;
		else
			quoteless[j++] = str[i];
	}
	quoteless[j] = '\0';
	return (quoteless);
}

char	*take_off_quotes(char *str)
{
	char	*quoteless;

	quoteless = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!quoteless)
	{
		free(str);
		return (NULL);
	}
	put_str_without_quotes(str, quoteless);
	free(str);
	return (quoteless);
}
