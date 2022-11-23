/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/23 13:35:26 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Les char **args sont les tableaux d'arguments des structures de commande,
en ayant pour case[0] le premier argument. Donc pour "ls -a", args[0] == -a.*/

/* Faire gaffe au code d'erreur, a bien retourner dans le parent si on est dans
un child et aussi si on retourne 1 ou 0*/

/*code d'erreur set a 0 par defaut*/

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

int	echo(t_lex *args)
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
			ft_printf("%s", args->str);
			if (args->next && args->next->str[0])
				ft_printf(" ");
		}
		args = args->next;
	}
	if (newline)
		ft_printf("\n");
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
		g_exit_status = 1; //code d'erreur a definir
		ft_printf("ERROR : need path in argument\n"); //a paufiner
		return (1);
	}
	if (args->next)
	{
		g_exit_status = 1;
		ft_printf("ERROR : to many arguments\n");//paufined
		return (1);
	}
	if (!chdir(args->str))
	{
		cd_modify_pwd_values(data);
		return (1);
	}
	g_exit_status = 1;
	perror("chdir");
	return (1);
}
/* Cd doit fonctionner qu'avec un chemin relatif ou absolu, donc pas de cd seul
*/

int	pwd(t_lex *args)
{
	char	*str;

	if (args && args->str[0] == '-')
	{
		printf("ERROR : bash: pwd: %c: invalid option\npwd: usage: pwd [-LP]\n", args->str[0]);
		g_exit_status = 2;
		return (1);
	}
	str = getcwd(NULL, 0);
	if (!str)
		return (0);
	ft_printf("%s\n", str);
	free(str);
	return (1);
}

int	env(t_data *data, t_lex *args)
{
	if (args)
	{
		if (args && args->str[0] == '-' && args->str[1])
		{
			printf("env: invalid option -- '%c'\nTry 'env --help' for more information.\n", args->str[1]);
		}
		else if (args && !args->str[0] == '-')
		{
			printf("ERROR : env: '%s': No such file or directory\n", args->str);
			g_exit_status = 127;
			return (1);
		}
	}
	if (data->env)
		ft_lstprint_lex(data->env);
	return (1);
}

int	ixit(t_data *data, t_lex *args)
{
	printf("exit\n");
	if (args && args->next)
	{
		printf("ERROR : bash: exit: too many arguments\n");
		return (1);
	}
	else if (args)
	{
		if (ft_str_isdigit(args->str))
			g_exit_status = ft_atoi(args->str);
		else
			printf("ERROR : bash: exit: %s: numeric argument required\n", args->str);
	}
	free_all_and_exit(data, "exit");
	return (1);
}
