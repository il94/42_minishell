/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/13 21:46:48 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Les char **args sont les tableaux d'arguments des structures de commande,
en ayant pour case[0] le premier argument. Donc pour "ls -a", args[0] == -a.*/

/* Faire gaffe au code d'erreur, a bien retourner dans le parent si on est dans
un child et aussi si on retourne 1 ou 0*/

/*code d'erreur set a 0 par defaut*/

int	echo(t_lex *args) //cas d'erreurs : syntax error donc a gerer avant
{
	t_lex	*start;

	start = args;
	if (args && !ft_strcmp(args->str, "-n"))
		args = args->next;
	while (args && args->str)
	{
		ft_printf("%s", args->str);
		if (args->next)
			ft_printf(" ");
		args = args->next;
	}
	if (!start || (start && ft_strcmp(start->str, "-n")))
		ft_printf("\n");
	return (1);
}

int	cd(t_lex *args)
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
		return (1);
	g_exit_status = 1;
	perror("chdir");
	return (1);
}
/* Cd doit fonctionner qu'avec un chemin relatif ou absolu, donc pas de cd seul
*/

int	pwd(t_lex *args)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);
	free(str);
	return (1);
}

int	env(t_data *data)
{
	ft_lstprint_lex(data->env);
	return (1);
}
