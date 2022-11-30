/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:39 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 14:07:56 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand(char *to_find, t_lex *env)
{
	if (*to_find == '$')
		to_find++;
	while (env && (ft_strncmp(to_find, env->str, ft_strlen(to_find))
			|| env->str[ft_strlen(to_find)] != '='))
			env = env->next;
	if (env)
		return (env->str + ft_strlen(to_find) + 1);
	return (NULL);
}

static char	*add_el_to_var(char *str, char *var_name, int *index_str)
{
	int	index_var_name;

	index_var_name = 0;
	while (str[(*index_str)] && (ft_isalnum(str[(*index_str)])
			|| is_there("?*_", str[(*index_str)])))
	{
		var_name[index_var_name++] = str[(*index_str)];
		if (str[(*index_str)++] == '?')
			break ;
	}
	var_name[index_var_name] = '\0';
	return (var_name);
}

static char	*expand_var(t_data *data, char *var_name, char *var_name_next)
{
	char	*var_content;
	char	*expanded;
	char	*e_status;

	e_status = NULL;
	if (!ft_strcmp(var_name, "?"))
	{
		e_status = ft_itoa(data->prev_exit_status);
		if (!e_status)
		{
			free(var_name);
			return (NULL);
		}
		expanded = e_status;
	}
	else
		expanded = expand(var_name, data->env);
	var_content = ft_strjoin(expanded, var_name_next);
	free(var_name);
	if (e_status)
		free(e_status);
	if (!var_content)
		return (NULL);
	return (var_content);
}

char	*return_env_var(t_data *data, char *str, int *index, char **tmp)
{
	char	*var_name;
	char	*var_content;
	int		index_str;

	index_str = 1;
	if (!str)
		return (NULL);
	if (str[index_str] == '\'' || str[index_str] == '\"')
		return (NULL);
	var_name = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	var_name = add_el_to_var(str, var_name, &index_str);
	var_content = expand_var(data, var_name, &str[index_str]);
	if (!var_content)
		return (NULL);
	*index = 0;
	*tmp = var_content;
	return (var_content);
}
