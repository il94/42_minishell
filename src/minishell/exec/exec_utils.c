/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:00:42 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 17:00:53 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	t_cmd	*result;
	
	result = ft_lstlast_cmd(cmd);
	if (result && result->child_cmd)
		return (get_last_cmd(result->child_cmd));
	return (result);
}
