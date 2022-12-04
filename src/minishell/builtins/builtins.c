/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 21:43:15 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(t_data *data)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
		free_all_and_exit(data, "getcwd");
	printf("%s\n", str);
	free(str);
}

void	env(t_data *data)
{
	if (data->env)
		ft_lstprint_lex(data->env);
}

void	unset(t_data *data, t_lex *args)
{
	t_lex	*target;

	if (!args || !args->str)
		return ;
	target = NULL;
	target = ft_lststrncmp_lex(&data->env, args->str, ft_strlen(args->str));
	if (target && !target->next && !target->prev)
		ft_lstclear_lex(&data->env);
	else if (target)
		ft_lstdelone_lex(target);
	if (args->next)
		unset(data, args->next);
}

void	ixit(t_data *data, t_lex *args, int in_child)
{
	if (!in_child)
		ft_printf_fd(2, "exit\n");
	if (args)
	{
		if ((!is_there("+-", args->str[0]) && !ft_str_isdigit(args->str))
			|| (is_there("+-", args->str[0]) && !ft_str_isdigit(&args->str[1])))
		{
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				args->str);
			g_exit_status = 2;
		}
		else if (args->next)
		{
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
			g_exit_status = 1;
			return ;
		}
		else
			g_exit_status = ft_atoi(args->str);
	}
	free_data_struct(data);
	if (data->start_env)
		free_lexer_struct(&(data->start_env));
	exit (g_exit_status);
}
