/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:12:24 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 18:33:44 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_unexpected_eof(char *delimiter)
{
	ft_printf_fd(2, "\nminishell: warning: here-document delimited by ");
	ft_printf_fd(2, "end-of-file (wanted `%s')\n", delimiter);
}

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

static int	len_buf(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (i == 0)
		return (1);
	return (i);
}

static void	writing_here_doc(t_data *data, char *delimiter, int fd)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	while (1)
	{
		printf("> ");
		buffer = ft_get_next_line(STDIN_FILENO);
		if (g_exit_status == 130)
			break ;
		else if (!buffer)
		{
			sig_unexpected_eof(delimiter);
			break ;
		}
		if (!ft_strncmp(delimiter, buffer, len_buf(buffer)))
			break ;
		if (ft_strchr(buffer, '$'))
			buffer = expand_in_hd(data, &buffer);
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	if (buffer)
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
	pid_here_doc = fork();
	if (pid_here_doc == -1)
		free_all_and_exit(data, "pipe");
	signal(SIGINT, sig_int_heredoc_parent);
	if (pid_here_doc == 0)
	{
		close(fd_here_doc[0]);
		signal(SIGINT, sig_int_heredoc_child);
		writing_here_doc(data, file->file, fd_here_doc[1]);
		free_all_and_exit(data, NULL);
	}
	wait(NULL);
	close(fd_here_doc[1]);
	signal(SIGINT, replace_sig_int);
	return ;
}
