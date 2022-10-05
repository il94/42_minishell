/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/05 14:21:03 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell(t_cmd *commands)
{
	char 		*str;

	while (1)
	{
		str = readline("minishellent> ");
		if (!ft_strcmp(str, "stop"))
		{
			free(str);
			break ;
		}
		if (str[0] != '\0')
			add_history(str);
		lexer(commands, str);
		//parsing
		//exec
		free(str);
	}
}