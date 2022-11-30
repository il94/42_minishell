/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:09:30 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 17:14:40 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_there(char *str, char in)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in == str[i])
			return (str[i]);
		i++;
	}
	return (0);
}

int	is_there_v2(char *is, char *there)
{
	int	i;

	if (!there)
		return (0);
	i = 0;
	while (there[i])
	{
		if (is_there(is, there[i]))
			return (there[i]);
		i++;
	}
	return (0);
}

int	is_there_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' && !is_in_quotes(str, &str[i]))
			return (1);
	}
	return (0);
}

int	is_there_el_outside_quotes(char *str, char el)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == el && !is_in_quotes(str, &str[i]))
			return (1);
	}
	return (0);
}

int	is_there_el_outside_quotes_v2(char *str, char *el)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (el[i])
	{
		if (is_there_el_outside_quotes(str, el[i]))
			return (1);
		i++;
	}
	return (0);
}
