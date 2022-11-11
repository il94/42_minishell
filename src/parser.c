/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:14:05 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/11 22:59:03 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*expand :
	si entre double quotes on va chercher la variable dans env
	si entre simple quotes on fait rien
	*/

// char	*check_str(t_data *data, char *str)
// {
// 	char	*new_str;

// 	if (!str)
// 		return (NULL);
// 	new_str = NULL;
// 	if (ft_strchr(str, '$'))
// 		new_str = check_expand(data, str, 0, 0);
// }
/*
void	parser(t_data *data)
{
	return ;
}*/