/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:56:55 by auzun             #+#    #+#             */
/*   Updated: 2022/11/27 18:01:53 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	msg_error(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	cmd_error(int status, char *cmd)
{
	msg_error("minishell: ");
	msg_error(cmd);
	if (status == 127)
		msg_error(": command not found\n");
	else if (status == 1)
		msg_error(": no shuch file or directory\n");
	else if (status == 2)
		msg_error(": filename argument required\n");
	else if (status == 126)
		msg_error(": is a directory\n");
	else if (errno)
	{
		msg_error(": ");
		msg_error(strerror(errno));
		msg_error("\n");
	}
}
