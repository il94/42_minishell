/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:56:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/08 18:27:51 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_standard_input(int ac)
{
	if (ac > 1)
	{
		ft_printf_fd(2, "Error: To many arguments\n");
		return (0);
	}
	if (!isatty(0))
	{
		ft_printf_fd(2, "Error: Invalid STDIN\n");
		return (0);
	}
	return (1);
}

void	set_parent_default_in_out(t_data *data)
{
	data->parent_in_fd = -1;
	data->parent_out_fd = -1;
}

void	initialize_data(t_data *data, char **envp)
{
	set_parent_default_in_out(data);
	data->prev_exit_status = 0;
	data->commands = NULL;
	data->start_cmd = NULL;
	data->lexer = NULL;
	data->start_lex = NULL;
	data->prompt = NULL;
	data->start_env = NULL;
	if (envp && envp[0])
	{
		data->start_env = ft_array_to_lst_lex(envp);
		if (!data->start_env)
			free_all_and_exit(data, "malloc");
	}
	data->env = data->start_env;
}
