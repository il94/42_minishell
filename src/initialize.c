/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:56:57 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/17 16:32:07 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize_data(t_data *data)
{
	data->commands = NULL;
	data->start_cmd = NULL;
	data->lexer = NULL;
	data->start_lex = NULL;
	data->prompt = NULL;
}
