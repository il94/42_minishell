/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:59:18 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/26 12:17:58 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Les char **args sont les tableaux d'arguments des structures de commande,
en ayant pour case[0] le premier argument. Donc pour "ls -a", args[0] == -a.*/

/* Faire gaffe au code d'erreur, a bien retourner dans le parent si on est dans
un child et aussi si on retourne 1 ou 0*/

int	echo(char **args) //cas d'erreurs : syntax error donc a gerer avant
{
	int	i;

	i = 0;
	if (!ft_strcmp(args[0], "-n"))
		i = 1;
	while (args && args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!args || !args[0] || ft_strcmp(args[0], "-n"))
		ft_printf("\n");
	return (0);		
}


int	cd(char **args)
{
	if (!args || !args[0])
	{
		g_exit_status = 1; //code d'erreur a definir
		ft_printf("ERROR : need path in argument\n"); //a paufiner
		return (1);
	}
	if (args[1])
	{
		g_exit_status = 1;
		ft_printf("ERROR : to many arguments\n");	//paufined
		return (1);
	}
	if (!chdir(args[0]))
		return (0);
	g_exit_status = 1;
	perror("chdir");
	return (1);
}
/* Cd doit fonctionner qu'avec un chemin relatif ou absolu, donc pas de cd seul
*/

int	pwd(char **args)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}
