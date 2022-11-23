/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:12:24 by auzun             #+#    #+#             */
/*   Updated: 2022/11/23 17:48:26 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	sig_unexpected_eof(char *delimiter)
{
	msg_error("\nminishell: ");
	msg_error("warning: here-document delimited by end-of-file (wanted `");
	msg_error(delimiter);
	msg_error("')\n");
}

static void	writing_here_doc(char *delimiter, int fd)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		ft_printf("> ");
		buffer = ft_get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			sig_unexpected_eof(delimiter);
			return ;
		}
		buffer[ft_strlen(buffer) - 1] = '\0';
		if (!ft_strcmp(delimiter, buffer))
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
	int		fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		free_all_and_exit(data, "pipe");
	file->fd = fd_here_doc[0];
	// delimiter = ft_strdup(file->file);
	pid_here_doc = fork();
	if (pid_here_doc == -1)
		free_all_and_exit(data, "pipe");
	if (pid_here_doc == 0)
	{
		signal(SIGINT, SIG_DFL);
		writing_here_doc(file->file, fd_here_doc[1]);
		close(fd_here_doc[1]);
		free_all_and_exit(data, NULL);
	}
	wait(NULL);
	// free(delimiter);
	close(fd_here_doc[1]);
	signal(SIGINT, replace_sig_int);
	return ;
}
