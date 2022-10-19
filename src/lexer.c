/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:58:21 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/19 18:48:22 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*expand dans le parser pour plus de faciliter chakalito si redi == $ on voit ca dans le parser 
si addcmd == $ dans le parser et si il y a plus d'un arg on met le rest au debut de la liste d'argument
si add arg == $ alors on ajoute dans arg a la fin

verif les '()' non fermes dans lex_init....
*/
void	ft_print_fd(t_fd *fd)
{
	while (fd)
	{
		printf("[%d] %s | ", fd->operator, fd->file);
		fd = fd->next;
	}
}
void	get_lexer(t_data *data)
{
	data->lexer = NULL;
	data->lexer = ft_lstsplit_charset_lex(data->prompt, "><&|() \t$\'\"");
	if (!data->lexer)
		free_all_and_exit(data, "malloc");
	data->start_lex = data->lexer;
	if (!concat_lexer(data))
		free_lexer_struct(&(data->start_lex));
	data->lexer = data->start_lex;
}

void	lexer(t_data *data)
{
	data->commands = ft_lstnew_cmd();
	if (!data->commands)
		free_all_and_exit(data, "malloc");
	data->start_cmd = data->commands;
	while (data->lexer)
	{
		if (!ft_strcmp(data->lexer->str, "&"))
		{
			printf("ERROR\n");
			break ;
		}
		define_delimiter(data);
		define_redi(data);
		define_argument(data);
		define_command(data);
		define_child(data);
		if (data->lexer)
			data->lexer = data->lexer->next;
	}
	data->lexer = data->start_lex;
	data->commands = data->start_cmd;
}
