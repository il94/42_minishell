/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:05 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/28 15:13:41 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*expand :
	si entre double quotes on va chercher la variable dans env
	si entre simple quotes on fait rien
	*/

char	*expand(char *to_find, t_lex *env)
{
	if (*to_find == '$')
		to_find++;
	while (env && (ft_strncmp(to_find, env->str, ft_strlen(to_find))
			|| env->str[ft_strlen(to_find)] != '='))
			env = env->next;
	if (env)
		return (env->str + ft_strlen(to_find) + 1);
	return (ft_strdup("\0"));
}

char	*return_env_var(t_data *data, char *str, int *index)
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
	*index += index_var_name;
	return (var_content);
}

char	*add_unsuspect_char(char *last, char *next, int *index, int *quotes)
{
	char	*new;
	int		index_new;
	char	*rvalue;

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
		else
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

/*void	*check_expand(t_data *data, char **str, int quotes, int *index_next)
{

}*/

void	exit_loop(t_data *data, char *new_str)
{
	if (new_str)
		free(new_str);
	free_all_and_exit(data, "malloc");
}

char	*check_str(t_data *data, char *str, int quotes, int err)
{
	char	*new_str;
	char	*tmp;
	int		index_new;
	int		index_next;

	index_next = 0;
	index_new = 0;
	new_str = NULL;
	while (str[index_next])
	{
		new_str = add_unsuspect_char(new_str, str, &index_next, &quotes);
		if (!new_str)
			exit_loop(data, new_str);
		if (!str[index_next])
			break ;
		if (str[index_next] == '$' && !is_there("\'\"", str[index_next + 1])
			&& (!quotes | quotes == '\"'))
		{
			tmp = return_env_var(data, &str[index_next], &index_next);
			index_next = 0;
			if (!tmp)
				exit_loop(data, new_str);
			free(str);
			str = tmp;
			tmp = NULL;
		}
		else if (str[index_next++] == '$')
		{
			tmp = ft_strjoin(new_str, "$");
			free(new_str);
			if (!tmp)
				free_all_and_exit(data, "malloc");
			new_str = tmp;
		}
	}
	return (new_str);
}
/*
void	parser(t_data *data)
{
	return ;
}*/