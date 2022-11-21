/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:12:24 by auzun             #+#    #+#             */
/*   Updated: 2022/11/21 06:38:00 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	opening_fd_here_doc(t_data *data, t_fd *file, char *here_doc_name)
{
	file->fd = open(here_doc_name, O_RDWR | O_EXCL | O_CREAT, 0644);
	if (file->fd == -1)
		define_exit_status("minishell: error: cant create heredoc.\n", 1);
}

static void	writing_here_doc(t_data *data, t_fd *file)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = ft_get_next_line(STDIN_FILENO);
		if (!buffer)
			free_all_and_exit(data, "malloc");
		buffer[ft_strlen(buffer) - 1] = '\0';
		if (!ft_strcmp(av[2], buffer))
			break ;
		write(file->fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(file->fd);
	file->fd = -1;
}

void	generate_here_doc(t_data *data, t_fd *file)
{
	char	*here_doc_name;

	/*here_doc_name = random_name...*/
	opening_fd_here_doc(data, fd);
	if (g_exit_status)
		return ;
	writing_here_doc(cmd_list, fd_list, av);
}