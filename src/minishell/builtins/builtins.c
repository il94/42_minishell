/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 15:55:56 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo_detect_n_flag(t_lex *args)
{
	int	i;

	i = 1;
	if (args->str[0] == '-')
	{
		while (args && args->str[i] && args->str[i] == 'n')
			i++;
		if (args->str[i] || i == 1)
			return (0);
		else
			return (1);
	}
	return (0);
}

int	echo(t_data *data, t_lex *args)
{
	t_bool	newline;

	newline = TRUE;
	while (args && echo_detect_n_flag(args))
	{
		newline = FALSE;
		args = args->next;
	}
	while (args && args->str)
	{
		if (args->str[0])
		{
			printf("%s", args->str);
			if (args->next && args->next->str[0])
				printf(" ");
		}
		args = args->next;
	}
	if (newline)
		printf("\n");
	return (1);
}

void	cd_modify_pwd_values(t_data *data)
{
	t_lex	*pwd;
	t_lex	*oldpwd;
	char	*str;

	oldpwd = ft_lststrncmp_lex(&data->env, "OLDPWD", 3);
	pwd = ft_lststrncmp_lex(&data->env, "PWD", 3);
	free(oldpwd->str);
	oldpwd->str = ft_strjoin("OLD", pwd->str);
	if (!oldpwd->str)
		free_all_and_exit(data, "malloc");
	free(pwd->str);
	str = getcwd(NULL, 0);
	if (!str)
		free_all_and_exit(data, "getcwd");
	pwd->str = ft_strjoin("PWD=", str);
	free(str);
	if (!pwd->str)
		free_all_and_exit(data, "malloc");
}

int	cd(t_data *data, t_lex *args)
{
	if (!args)
	{
		g_exit_status = 1;
		msg_error("minishell: cd: path argument required\n");
		return (1);
	}
	if (args->next)
	{
		g_exit_status = 1;
		msg_error("minishell: cd: to many arguments\n");
		return (1);
	}
	if (!chdir(args->str))
	{
		cd_modify_pwd_values(data);
		return (1);
	}
	g_exit_status = 1;
	msg_error("minishell: cd: ");
	perror(args->str);
	return (1);
}

int	pwd(t_data *data, t_lex *args)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
		free_all_and_exit(data, "getcwd");
	ft_printf("%s\n", str);
	free(str);
	return (1);
}

int	env(t_data *data, t_lex *args)
{
	if (data->env)
		ft_lstprint_lex(data->env);
	return (1);
}

int	ixit(t_data *data, t_lex *args)
{
	printf("exit\n");
	if (args && args->next)
	{
		if (!ft_str_isdigit(args->str))
		{
			msg_error("minishell: exit: ");
			msg_error(args->str);
			msg_error(": numeric argument required\n");
			g_exit_status = 2;
		}
		else
		{
			msg_error("minishell: exit: too many arguments\n");
			g_exit_status = 1;
			return (1);
		}
	}
	else if (args)
	{
		if (ft_str_isdigit(args->str))
			g_exit_status = ft_atoi(args->str);
		else
		{
			msg_error("minishell: exit: ");
			msg_error(args->str);
			msg_error(": numeric argument required\n");
			g_exit_status = 2;
		}
	}
	free_data_struct(data);
	if (data->start_env)
		free_lexer_struct(&(data->start_env));
	exit (g_exit_status);
	return (1);
}
