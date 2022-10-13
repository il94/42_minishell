/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:12:37 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/13 16:51:55 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer_struct(t_lex **lexer)
{
	if ((*lexer)->next)
		free_lexer_struct(&((*lexer)->next));
	if ((*lexer)->content)
		free((*lexer)->content);
	free((*lexer));
	(*lexer) = NULL;
}

void	free_fd_struct(t_fd *list)
{
	if (list->next)
		free_fd_struct(list->next);
	if (list->fd != -1)
		close(list->fd);
	if (list->file)
		free(list->file);
	free(list);
}

void	free_command_struct(t_cmd **commands)
{
	if ((*commands)->next)
		free_command_struct((&(*commands)->next));
	if ((*commands)->input)
		free_fd_struct((*commands)->input);
	if ((*commands)->output)
		free_fd_struct((*commands)->output);
	if ((*commands)->command)
		free((*commands)->command);
	if ((*commands)->args)
		ft_free_array((*commands)->args);
	if ((*commands)->child_cmd)
		free_command_struct((&(*commands)->child_cmd));
	free((*commands));
	(*commands) = NULL;
}

void	free_all_and_exit(t_data *data, char *str_error)
{
	if (data->commands)
		free_command_struct(&(data->commands));
	if (data->lexer)
		free_lexer_struct(&(data->lexer));
	if (data->prompt)
		free(data->prompt);
	if (str_error)
		perror(str_error);
	exit (1);
}
