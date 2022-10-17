/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/17 20:20:57 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_file(t_data *data)
{
	char	*file;
	t_redi	r;
	
	r = define_redi(data->lexer);
	if (r == NOTHING_R || r == PIPE_R)
		return (NULL);
	data->lexer = data->lexer->next;
	while (data->lexer && is_there(" &|()<>", *(data->lexer->content)))
	{
		if (data->lexer && is_there("&|()<>", *(data->lexer->content)))
			return (NULL);
		data->lexer = data->lexer->next;
	}
	if (!data->lexer || !data->lexer->content)
		return (NULL);
	file = ft_strdup(data->lexer->content);
	if (!file)
		free_all_and_exit(data, "malloc");
	return (file);
}

t_fd	*add_fd_info(t_data *data)
{
	t_fd	*el;
	int		redi;

	redi = define_redi(data->lexer);
	if (redi == NOTHING_R)
		return (NULL);
	el = ft_lstnew_fd();
	if (!el)
		free_all_and_exit(data, "malloc");
	el->operator = redi;
	el->file = find_file(data);
	return (el);
}

int		add_redi_info(t_data *data)
{
	t_fd	*new_redi;
	int		redi;
	
	// redi = define_redi(data->lexer);
	// if (redi == NOTHING_R)
	// 	return (NULL);
	if (redi == PIPE_R)
	{
		ft_lstadd_back_fd(&(data->commands->input), add_fd_info(data));
		if (data->commands->prev)
			ft_lstadd_back_fd(&(data->commands->prev->output), add_fd_info(data));
	}
	else if (redi == L_CHEVRON
		|| redi == L_DOUBLE_CHEVRON)
		ft_lstadd_back_fd(&(data->commands->input), add_fd_info(data));
	else if (redi == R_CHEVRON
		|| redi == R_DOUBLE_CHEVRON)
		ft_lstadd_back_fd(&(data->commands->output), add_fd_info(data));
	return (1);
}

void	define_delimiter(t_data *data)
{
	data->commands->delimiter = get_delimiter(data->lexer);
	if (data->commands->delimiter)
	{
		ft_lstadd_back_cmd(&data->commands, ft_lstnew_cmd());
		if (!data->commands->next)
			free_all_and_exit(data, "malloc");
		data->commands = data->commands->next;
	}
}


void	lexer(t_data *data)
{
	data->commands = ft_lstnew_cmd();
	if (!data->commands)
		free_all_and_exit(data, "malloc");
	data->start_cmd = data->commands;
	while (data->lexer)
	{
		if (!ft_strcmp(data->lexer->content, "&"))
		{
			printf("ERROR\n"); // afficher le bon message
			break ;
		}
		define_delimiter(data);
		if (data->commands->prev && data->commands->prev->delimiter)
			printf("delimiterent = %d\n", data->commands->prev->delimiter);			
		add_redi_info(data);
		if (data->commands->input)
			printf("inpute = %s\n", data->commands->input->file);
		if (data->commands->output)
			printf("outepute = %s\n", data->commands->output->file);
		/* A effectuer dans define files ou redi */
		// if ((data->data->commands)->delimiter == PIPE_D)
		// 	(data->data->commands)->next->input->operator = PIPE_R;
		data->lexer = data->lexer->next;
	}
	data->lexer = data->start_lex;
	data->commands = data->start_cmd;
}
