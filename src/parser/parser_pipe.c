/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:42:31 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 12:48:52 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	generate_pipe(t_data *data, t_fd *file, t_cmd *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		free_all_and_exit(data, "pipe");
	file->fd = pipe_fd[1];
	if (cmd && cmd->next)
		cmd->next->input->fd = pipe_fd[0];
}
