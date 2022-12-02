/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:56:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/02 22:55:25 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
