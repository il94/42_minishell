/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:01 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 13:35:25 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_unsuspect_char(char *last, char *next, int *index, int *quotes)
{
	char	*new;
	int		index_new;
	char	*rvalue;

	rvalue = NULL;
	new = malloc((ft_strlen(next) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	index_new = 0;
	while (next[*index] && (next[*index] != '$'))
	{
		if (!(*quotes) && is_there("\'\"", next[*index]))
			*quotes = next[(*index)];
		else if (*quotes == next[*index])
			*quotes = 0;
		new[index_new++] = next[(*index)];
		(*index)++;
	}
	new[index_new] = '\0';
	rvalue = ft_strjoin(last, new);
	free(new);
	if (!rvalue)
		return (NULL);
	free(last);
	return (rvalue);
}

static void	*dont_expand(t_data *data, char **new_str)
{
	char	*tmp;

	tmp = ft_strjoin(*new_str, "$");
	free(*new_str);
	if (!tmp)
		free_all_and_exit(data, "malloc");
	*new_str = tmp;
}

static void	exit_loop(t_data *data, char *new_str, char *str)
{
	if (new_str)
		free(new_str);
	if (str)
		free(str);
	free_all_and_exit(data, "malloc");
}

char	*check_expand(t_data *data, char **str, int quotes, int n)
{
	char	*new_str;
	char	*tmp;
	int		index_new;

	index_new = 0;
	new_str = NULL;
	while ((*str)[n])
	{
		new_str = add_unsuspect_char(new_str, (*str), &n, &quotes);
		if (!new_str)
			exit_loop(data, new_str, (*str));
		if (!(*str)[n])
			break ;
		if ((*str)[n] == '$' && ((*str)[n + 1] && !is_there("\'\" ", (*str)[n + 1])
			&& (ft_isalnum((*str)[n + 1]) || is_there("?*_", (*str)[n + 1])))
			&& ((!quotes || quotes == '\"') || g_exit_status == 42))
		{
			if (!return_env_var(data, &(*str)[n], &n, &tmp))
				exit_loop(data, new_str, (*str));
			free((*str));
			(*str) = tmp;
		}
		else if (/*(*str)[n++] == '$' && !is_there("\'\"", (*str)[n])*/ (*str)[n++] == '$' && (!is_there("\'\"", (*str)[n]) || quotes))
			dont_expand(data, &new_str);
	}
	return (new_str);
}
