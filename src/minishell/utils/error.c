/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:56:55 by auzun             #+#    #+#             */
/*   Updated: 2022/11/30 18:00:46 by ilandols         ###   ########.fr       */
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
	ft_printf_fd(2, "minishell: %s", cmd);
	if (status == 127)
		ft_printf_fd(2, ": command not found\n");
	else if (status == 1)
		ft_printf_fd(2, ": no such file or directory\n");
	else if (status == 2)
		ft_printf_fd(2, ": filename argument required\n");
	else if (status == 126)
		ft_printf_fd(2, ": is a directory\n");
	else if (errno)
		ft_printf_fd(2, ": %s\n", strerror(errno));
}

void	define_exit_status(char *to_print, int error_code)
{
	if (to_print)
		ft_printf_fd(2, to_print);
	g_exit_status = error_code;
}
