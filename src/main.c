/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:47 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/11 17:03:53 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

void	minishell_test(t_data *data, char **av)
{
	t_lex	*new;
	t_lex	*lst;

	while (1)
	{
		data->prompt = readline("minishellent> ");
		if (!ft_strcmp(data->prompt, "stop"))
		{
			free(data->prompt);
			data->prompt = NULL;
			break ;
		}
		if (data->prompt[0] != '\0')
		{	
			add_history(data->prompt);
			get_lexer(data);
			// ft_lstprint_lex(data->lexer);
			if (data->lexer)
			{
				lexer(data);
				// print_cmd(data->commands, "PARENT");
				// parser(data);
			}
			if (!ft_strncmp(data->prompt, "echo", 4))
				echo(data->commands->args);
			else if (!ft_strncmp(data->prompt, "cd", 2))
				cd(data->commands->args);
			else if (!ft_strncmp(data->prompt, "pwd", 3))
				pwd(data->commands->args);
			else if (!ft_strncmp(data->prompt, "env", 3))
				env(data);
			else if (!ft_strncmp(data->prompt, "export", 6))
				exporc(data, data->commands->args);
			else if (ft_strchr(data->prompt, '*'))
			{
				new = ft_lstnew_lex(ft_strdup(data->prompt));
				lst = ft_wildcard(data, new);
				if (lst)
				{
					ft_lstprint_lex(lst);
					free_lexer_struct(&lst);
				}
				/*else if (new)
					free_lexer_struct(&new);*/
			}
			else if (ft_strchr(data->prompt, '$'))
			{
				new = ft_expand(data, ft_strdup(data->prompt));
				if (new)
				{
					ft_lstprint_lex(new);
					free_lexer_struct(&new);
				}
			}
			g_exit_status = 0;
		}
		free_data_struct(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	g_exit_status = 0;
	initialize_data(&data, envp);
	// minishell(&data);
	minishell_test(&data, av);
	if (data.start_env)
		free_lexer_struct(&data.start_env);
	free_data_struct(&data);
	return (0);
}
