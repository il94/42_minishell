/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:12:37 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/05 14:19:14 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all_and_exit(t_cmd *commands, char *str_error)
{
	if (commands)
		ft_lstclear(&commands);	
	if (str_error)
		perror(str_error);
	exit (1);
}