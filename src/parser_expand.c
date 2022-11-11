/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:01 by auzun             #+#    #+#             */
/*   Updated: 2022/11/11 16:49:49 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*return_env_var(t_data *data, char *str, int *index, char **tmp)
{
	char	*var_name;
	char	*var_content;
	int		index_str;
	int		index_var_name;

	index_str = 1;
	if (!str)
		return (NULL);
	if (str[index_str] == '\'' || str[index_str] == '\"')
		return (NULL);
	var_name = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	index_var_name = 0;
	while (str[index_str] && (ft_isalnum(str[index_str])
			|| str[index_str] == '_'))
		var_name[index_var_name++] = str[index_str++];
	var_name[index_var_name] = '\0';
	var_content = ft_strjoin(expand(var_name, data->env), &str[index_str]);
	free(var_name);
	if (!var_content)
		return (NULL);
	*index = 0;
	*tmp = var_content;
	return (var_content);
}

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
	int i = 0;
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

char	*check_expand(t_data *data, char *str, int quotes, int n)
{
	char	*new_str;
	char	*tmp;
	int		index_new;

	index_new = 0;
	new_str = NULL;
	while (str[n])
	{
		new_str = add_unsuspect_char(new_str, str, &n, &quotes);
		if (!new_str)
			exit_loop(data, new_str, str);
		if (!str[n])
			break ;
		if (str[n] == '$' && (str[n + 1] && !is_there("\'\"", str[n + 1]))
			&& (!quotes || quotes == '\"'))
		{
			if (!return_env_var(data, &str[n], &n, &tmp))
				exit_loop(data, new_str, str);
			free(str);
			str = tmp;
		}
		else if (str[n++] == '$' && !is_there("\'\"", str[n]))
			dont_expand(data, &new_str);
	}
	if (str)
		free(str);
	return (new_str);
}
