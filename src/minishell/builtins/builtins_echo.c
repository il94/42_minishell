/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:18:11 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 20:32:49 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	echo_detect_n_flag(t_lex *args)
{
	int	i;

	i = 1;
	if (args->str[0] == '-')
	{
		while (args && args->str[i] && args->str[i] == 'n')
			i++;
		if (args->str[i] || i == 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	echo(t_lex *args)
{
	t_bool	newline;

	newline = TRUE;
	while (args && echo_detect_n_flag(args))
	{
		newline = FALSE;
		args = args->next;
	}
	while (args && args->str)
	{
		if (args->str)
		{
			ft_printf("%s", args->str);
			if (args->next && args->next->str)
				ft_printf(" ");
		}
		args = args->next;
	}
	if (newline)
		ft_printf("\n");
}
