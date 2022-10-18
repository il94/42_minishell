/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:36:53 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 17:31:46 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_file(t_data *data)
{
	char	*file;
	t_redi	r;
	t_lex	*temp;

	temp = data->lexer;
	r = get_redi(data->lexer);
	if (r == NOTHING_R || r == PIPE_R)
		return (NULL);
	data->lexer = data->lexer->next;
	while (data->lexer && is_there(" &|()<>", *(data->lexer->str)))
	{
		if (data->lexer && is_there("&|()<>", *(data->lexer->str)))
		{
			data->lexer = temp;
			return (NULL);
		}
		data->lexer = data->lexer->next;
	}
	if (!data->lexer || !data->lexer->str)
	{
		data->lexer = temp;
		return (NULL);
	}
	file = ft_strdup(data->lexer->str);
	if (!file)
		free_all_and_exit(data, "malloc");
	data->lexer = temp;
	return (file);
}

t_fd	*define_fd(t_data *data)
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
	t_fd	*new_redi;
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
