/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:10:33 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/19 18:08:31 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_istoken(int c)
{
	return (is_there(TOKENS, c));
}

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

t_redi	get_redi(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_R);
	if (!ft_strcmp(element->str, "<"))
		return (L_CHEVRON);
	if (!ft_strcmp(element->str, "<<"))
		return (L_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, ">"))
		return (R_CHEVRON);
	if (!ft_strcmp(element->str, ">>"))
		return (R_DOUBLE_CHEVRON);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_R);
	return (NOTHING_R);
}

t_deli	get_delimiter(t_lex *element)
{
	if (!element || !element->str)
		return (NOTHING_D);
	if (!ft_strcmp(element->str, "|"))
		return (PIPE_D);
	if (!ft_strcmp(element->str, "&&"))
		return (AND);
	if (!ft_strcmp(element->str, "||"))
		return (OR);
	return (NOTHING_D);
}
