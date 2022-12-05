/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:18:51 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/04 20:33:00 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cd_modify_pwd_values(t_data *data)
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

void	cd(t_data *data, t_lex *args)
{
	if (!args)
	{
		g_exit_status = 1;
		ft_printf_fd(2, "minishell: cd: path argument required\n");
		return ;
	}
	if (args->next)
	{
		g_exit_status = 1;
		ft_printf_fd(2, "minishell: cd: to many arguments\n");
		return ;
	}
	if (!chdir(args->str))
	{
		if (data->env)
			cd_modify_pwd_values(data);
		return ;
	}
	g_exit_status = 1;
	ft_printf_fd(2, "minishell: cd: ");
	perror(args->str);
}
