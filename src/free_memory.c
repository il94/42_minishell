/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:12:37 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/06 16:18:26 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	free_command_struct(t_cmd *commands)
{
	if (commands->next)
		free_command_struct(commands->next);
	if (commands->input)
		free_fd_struct(commands->input);
	if (commands->output)
		free_fd_struct(commands->output);
	if (commands->command)
		free(commands->command);
	if (commands->args)
		ft_free_array(commands->args);
	if (commands->child_cmd)
		free_command_struct(commands->child_cmd);
	free(commands);
}

void	free_all_and_exit(t_cmd *commands, char *str_error)
{
	if (commands)
		free_command_struct(commands);
	if (str_error)
		perror(str_error);
	exit (1);
}
