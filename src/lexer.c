/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/07 15:36:42 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	search_quotes(char **strings)
{
	int	i;
	int	j;

	i = 0;
	while (strings[i])
	{
		if (strings[i][0] == '\'')
		{
			j = i + 1;
			while (strings[j] && strings[j][0] != '\'')
			{
				strings[i] = ft_strjoin_free(strings[i], strings[j]);
				j++;
			}
			if (strings[j])
			{
				strings[i] = ft_strjoin_free(strings[i], strings[j]);
				j++;
			}
		}
		i++;
	}
}

void	lexer(t_cmd *commands, char *input)
{
	char	**strings;

	strings = ft_split_charset(input, " -$\'\"");
	if (!strings)
		return ;
	ft_print_array(strings);
	search_quotes(strings);
	ft_free_array(strings);
	// commands = ft_lstnew
}
