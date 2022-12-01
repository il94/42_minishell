/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:46:50 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 21:19:22 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exporc_normal_mode(t_data *data, t_lex *arg, int i)
{
	t_lex	*current;
	t_lex	*new;

	new = ft_lstnew_lex_dup(ft_strdup(arg->str));
	if (!new)
		free_all_and_exit(data, "malloc");
	current = ft_lststrncmp_lex(&data->env, arg->str, i + 1);
	if (current)
		ft_lstdelone_lex(current);
	ft_lstadd_back_lex(&data->env, new);
}

void	exporc_append_mode(t_data *data, t_lex *arg, int i)
{
	char	*arg_append_mode;
	t_lex	*current;
	t_lex	*new;

	arg_append_mode = ft_delete_char(arg->str, i - 1);
	if (!arg_append_mode)
		free_all_and_exit(data, "malloc");
	new = ft_lstnew_lex(arg_append_mode);
	if (!new)
		free_all_and_exit(data, "malloc");
	current = ft_lststrncmp_lex(&data->env, new->str, i);
	if (current)
	{
		current->str = ft_strjoin_free(current->str, &new->str[i]);
		ft_lstdelone_lex(new);
		if (!current->str)
			free_all_and_exit(data, "malloc");
	}
	else
		ft_lstadd_back_lex(&data->env, new);
}

int	exporc_parsing_argument(t_lex *arg, int i)
{
	if ((!ft_isalnum(arg->str[i]) && arg->str[i] != '+' && arg->str[i] != '_')
		|| (arg->str[i] == '+' && arg->str[i + 1] != '='))
	{
		g_exit_status = 1;
		ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
			arg->str);
		return (0);
	}
	return (1);
}

void	exporc(t_data *data, t_lex *arg)
{
	int		i;

	if (!arg || !arg->str)
		return (define_exit_status(NULL, 0));
	if (arg->str[0] == '=' || ft_isdigit(arg->str[0]))
	{
		g_exit_status = 1;
		ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
			arg->str);
		return ;
	}
	i = 0;
	while (arg->str[i] && arg->str[i] != '=')
	{
		if (!exporc_parsing_argument(arg, i))
			return ;
		i++;
	}
	if (!arg->str[i])
		return ;
	if (arg->str[i - 1] == '+')
		exporc_append_mode(data, arg, i);
	else
		exporc_normal_mode(data, arg, i);
}
