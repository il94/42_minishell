/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:46:50 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/06 11:23:30 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exporc_print_msg_error(char *str)
{
	g_exit_status = 1;
	ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", str);
}

static void	exporc_normal_mode(t_data *data, t_lex *arg, int i)
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

static void	exporc_append_mode(t_data *data, t_lex *arg, int i)
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

static int	exporc_parsing_argument(t_lex *arg, int i)
{
	if ((!ft_isalnum(arg->str[i]) && arg->str[i] != '+' && arg->str[i] != '_')
		|| (arg->str[i] == '+' && arg->str[i + 1] != '='))
		return (0);
	return (1);
}

void	exporc(t_data *data, t_lex *args)
{
	int		i;
	t_bool	error;

	error = FALSE;
	if (!args || !args->str)
		return (define_exit_status(NULL, 0));
	i = 0;
	while (args->str[i] && args->str[i] != '='
		&& exporc_parsing_argument(args, i))
		i++;
	if (i == 0)
		error = TRUE;
	if (args->str[i])
	{
		if (!error && args->str[i - 1] == '+')
			exporc_append_mode(data, args, i);
		else if (!error)
			exporc_normal_mode(data, args, i);
		else
			exporc_print_msg_error(args->str);
	}
	if (args->next)
		exporc(data, args->next);
}
