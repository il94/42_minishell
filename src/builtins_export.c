/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:46:50 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/13 21:46:59 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exporc_normal_mode(t_data *data, t_lex *args, int i)
{
	t_lex	*current;
	t_lex	*new;

	new = ft_lstnew_lex(ft_strdup(args->str)); //à remplacer par lstnewdup
	if (!new || !new->str)
		return (0);
	current = ft_lststrncmp_lex(&data->env, args->str, i + 1);
	if (current)
		ft_lstdelone_lex(current);
	ft_lstadd_back_lex(&data->env, new);
	return (1);
}

int	exporc_append_mode(t_data *data, t_lex *args, int i)
{
	char	*arg_append_mode;
	t_lex	*current;
	t_lex	*new;

	arg_append_mode = ft_delete_char(args->str, i - 1);
	if (!arg_append_mode)
		return (0);
	new = ft_lstnew_lex(arg_append_mode);
	if (!new)
		return (0);
	current = ft_lststrncmp_lex(&data->env, new->str, i);
	if (current)
	{
		current->str = ft_strjoin_free(current->str, &new->str[i]);
		ft_lstdelone_lex(new);
		if (!current->str)
			return (0);
	}
	else
		ft_lstadd_back_lex(&data->env, new);
	return (1);
}

int	exporc(t_data *data, t_lex *args)
{
	int		i;

	if (!args || !args->str) //si il n'y a pas d'argument, à reverifier
		return (define_exit_status(NULL, 0), 1);
	if (args->str[0] == '=' || ft_isdigit(args->str[0]))
		return (define_exit_status("ERROR\n", 1), 1);
	i = 0;
	while (args->str[i] && args->str[i] != '=')
	{
		if (!ft_isalnum(args->str[i])
			&& (args->str[i] == '+' && args->str[i + 1] != '='))
			return (define_exit_status("ERROR\n", 1), 1);
		i++;
	}
	if (!args->str[i])
		return (define_exit_status(NULL, 1), 1);
	if (args->str[i - 1] == '+')
		return (exporc_append_mode(data, args, i));
	return (exporc_normal_mode(data, args, i));
}
