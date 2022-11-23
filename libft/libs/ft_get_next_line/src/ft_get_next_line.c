/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:42:55 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/23 21:50:43 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"
#include "../../../../include/minishell.h"

char	*ft_get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			size_read;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	line = ft_strjoin_gnl(line, buffer[fd]);
	size_read = BUFFER_SIZE;
	while (!(is_end_of_line(line) || size_read != BUFFER_SIZE))
	{
		size_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (g_exit_status == 130)
		{
			free(line);
			return (NULL);
		}
		if (size_read < 0)
			return (NULL);
		buffer[fd][size_read] = '\0';
		line = ft_strjoin_gnl(line, buffer[fd]);
	}
	if (!line[0])
	{
		free(line);
		return (NULL);
	}
	else
		get_line(line, buffer[fd]);
	return (line);
}
