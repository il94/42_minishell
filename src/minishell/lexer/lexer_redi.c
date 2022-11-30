/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:36:53 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 23:00:20 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*near_unexpected_token(t_data *data, t_lex *temp, char *token)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		token);
	define_exit_status(NULL, 2);
	data->lexer = temp;
	return (NULL);
}

static void	*reload_lexer(t_data *data, t_lex *temp)
{
	near_unexpected_token(data, temp, "newline");
	data->lexer = temp;
	return (NULL);
}

static char	*find_file(t_data *data)
{
	char	*file;
	t_redi	r;
	t_lex	*temp;

	temp = data->lexer;
	r = get_redi(data->lexer);
	if (r == NOTHING_R || r == PIPE_R)
		return (NULL);
	data->lexer = data->lexer->next;
	while (data->lexer && (ft_iswhitespace(*(data->lexer->str))
			|| is_token(data->lexer)
			|| is_there_el_outside_quotes_v2(data->lexer->str, "()")))
	{
		if (data->lexer && (is_token(data->lexer)
				|| is_there_v2("()", data->lexer->str)))
			return (near_unexpected_token(data, temp, data->lexer->str));
		data->lexer = data->lexer->next;
	}
	if (!data->lexer || !data->lexer->str)
		return (reload_lexer(data, temp));
	file = ft_strdup(data->lexer->str);
	if (!file)
		free_all_and_exit(data, "malloc");
	data->lexer = temp;
	return (file);
}

static t_fd	*define_fd(t_data *data)
{
	t_fd	*el;
	int		redi;

	redi = get_redi(data->lexer);
	if (redi == NOTHING_R)
		return (NULL);
	el = ft_lstnew_fd();
	if (!el)
		free_all_and_exit(data, "malloc");
	el->operator = redi;
	el->file = find_file(data);
	return (el);
}

int	define_redi(t_data *data)
{
	t_redi	redi;

	redi = get_redi(data->lexer);
	if (redi == L_CHEVRON || redi == L_DOUBLE_CHEVRON || redi == PIPE_R)
	{
		ft_lstadd_back_fd(&(data->commands->input), define_fd(data));
		if (redi == PIPE_R && data->commands->prev)
			ft_lstadd_back_fd(&(data->commands->prev->output), define_fd(data));
	}
	else if (redi == R_CHEVRON || redi == R_DOUBLE_CHEVRON)
		ft_lstadd_back_fd(&(data->commands->output), define_fd(data));
	return (1);
}
