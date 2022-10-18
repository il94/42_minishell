/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:56:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 18:46:08 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize_data(t_data *data, char **envp)
{
	data->commands = NULL;
	data->start_cmd = NULL;
	data->lexer = NULL;
	data->start_lex = NULL;
	data->prompt = NULL;
	data->start_env = NULL;
	if (envp)
	{
		data->start_env = ft_array_to_lst_lex(envp);
		if (!data->start_env)
			free_all_and_exit(data, "malloc");
	}
	data->env = data->start_env;
}
