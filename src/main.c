/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:47 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/20 15:38:22 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_status;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	initialize_data(&data, envp);
	minishell(&data);
	if (data.start_env)
		free_lexer_struct(&(data.start_env));
	free_data_struct(&data);
	return (0);
}
