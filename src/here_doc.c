/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:12:24 by auzun             #+#    #+#             */
/*   Updated: 2022/11/22 23:51:07 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_unexpected_eof(char *delimiter)
{
	msg_error("minishell: ");
	msg_error("warning: here-document delimited by end-of-file (wanted `");
	msg_error(delimiter);
	msg_error("')\n");
}

static void	writing_here_doc(t_data *data, t_fd *file, int fd)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		ft_printf("> ");
		buffer = ft_get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			sig_unexpected_eof(file->file);
			return ;
		}
		buffer[ft_strlen(buffer) - 1] = '\0';
		if (!ft_strcmp(file->file, buffer))
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
}

void	generate_here_doc(t_data *data, t_fd *file)
{
	pid_t	pid_here_doc;
	int		fd_here_doc;

	if (pipe(fd_here_doc) == -1)
		free_all_and_exit(data, "pipe");
	file->fd = fd_here_doc[0];
	pid = fork()
	if (pid == -1)
		free_all_and_exit(data, "pipe");
	if (pid == 0)
	{
		writing_here_doc(cmd_list, fd_list, av);
		free_data_struct(data);
		close(fd_here_doc[1]);
		exit (0);
	}
	wait(NULL);
	close(fd_here_doc[1]);
	return ;
}

