/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:56:55 by auzun             #+#    #+#             */
/*   Updated: 2022/12/03 00:52:40 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	msg_error(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	unexpected_token(t_deli token, int v_mini)
{
	char	*deli;

	deli = get_deli_char(token);
	if (!deli)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `)'\n");
	else if (!v_mini)
		ft_printf_fd(2, "minishell: syntax error near unexpected token `");
	else
		ft_printf_fd(2,
			"minishell: syntax error (minishell) near unexpected token `");
	if (deli)
		ft_printf_fd(2, "%s'\n", deli);
	define_exit_status(NULL, 2);
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
