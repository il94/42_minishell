/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:06:55 by auzun             #+#    #+#             */
/*   Updated: 2022/12/04 21:40:23 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_there_in_out(t_cmd *cmd)
{
	t_fd	*f;

	if (!cmd)
		return (0);
	f = cmd->input;
	if (f && ((f->operator != PIPE_R
				&& f->operator != NOTHING_R) || cmd->input->next))
		return (1);
	return (0);
}
