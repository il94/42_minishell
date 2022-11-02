/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:01:04 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/02 17:32:22 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	minishell(t_data *data)
{
	while (1)
	{
		data->prompt = readline("minishellent> ");
		ft_lstprint_lex(wildiwonkard(data, data->prompt));
		//test_apply(data->prompt);
		if (!ft_strncmp(data->prompt, "cd", 2))
		{
			get_lexer(data);
			if (data->lexer)
				lexer(data);
			cd(&data->commands->args->str);
		}
		//printf("check_expand = %s\n", check_expand(data, data->prompt, 0, 0));
		/*t_lex *ls = send_dir_content(data->prompt, data, 0);
		ft_lstprint_lex(ls);
		ft_lstclear_lex(&ls);*/
		
		//printf("str = %s \n", check_expand(data, ft_strdup("\"$\"LANG$LANG-\" \'\"$LANG\'et toi$LANG "), 0, 0));
		/*if (!ft_strcmp(data->prompt, "stop"))
		{
			free(data->prompt);
			data->prompt = NULL;
			break ;
		}
		if (data->prompt[0] != '\0')
		{	
			add_history(data->prompt);
			get_lexer(data);
			ft_lstprint_lex(data->lexer);
			if (data->lexer)
			{
				lexer(data);
				print_cmd(data->commands, "PARENT");
				//parser(data);
			}
			g_exit_status = 0;
		}
		free_data_struct(data);*/
	}
}
