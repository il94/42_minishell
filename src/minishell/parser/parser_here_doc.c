/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:12:24 by auzun             #+#    #+#             */
/*   Updated: 2022/12/08 17:22:17 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*expand_in_hd(t_data *data, char **buffer)
{
	char	*tmp;
	int		last_status;

	last_status = g_exit_status;
	g_exit_status = 42;
	tmp = check_expand(data, buffer, 0, 0);
	free(*buffer);
	g_exit_status = last_status;
	return (tmp);
}

static void	writing_here_doc(t_data *data, char *delimiter, int fd)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (g_exit_status == 130)
			break ;
		else if (!buffer)
		{
			sig_unexpected_eof(delimiter);
			break ;
		}
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_strchr(buffer, '$'))
			buffer = expand_in_hd(data, &buffer);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	if (buffer)
		free(buffer);
}

void	generate_here_doc(t_data *data, t_fd *file)
{
	pid_t	pid_here_doc;
	int		fd_here_doc[2];

	if (pipe(fd_here_doc) == -1)
		free_all_and_exit(data, "pipe");
	file->fd = fd_here_doc[0];
	pid_here_doc = fork();
	if (pid_here_doc == -1)
		free_all_and_exit(data, "pipe");
	signal(SIGINT, sig_int_heredoc_parent);
	if (pid_here_doc == 0)
	{
		close(fd_here_doc[0]);
		signal(SIGINT, sig_int_heredoc_child);
		writing_here_doc(data, file->file, fd_here_doc[1]);
		close(fd_here_doc[1]);
		free_all_and_exit(data, NULL);
	}
	wait(NULL);
	close(fd_here_doc[1]);
	signal(SIGINT, replace_sig_int);
	return ;
}
