/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:47 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/27 16:18:25 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

void	sig_int_heredoc_child(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	close(0);
	g_exit_status = 130;
}

void	sig_int_heredoc_parent(int signum)
{
	(void)signum;
	g_exit_status = 130;
}

void	replace_sig_int(int signum)
{
	(void)signum;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	minishell_test(t_data *data, char **av)
{
	t_lex	*new;
	t_lex	*lst;

	while (1)
	{
		data->prompt = readline("\x1b[33msalam khey> \x1b[0m");
		if (!data->prompt)
			free_all_and_exit(data, "exit");
		g_exit_status = 0;
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
				parser(data, data->commands, 0);
				if (!g_exit_status)
					print_cmd(data->commands, "PARENT");
				exec(data, data->commands);
			}
			// if (!ft_strncmp(data->prompt, "echo", 4))
			// 	echo(data->commands->args);
			// else if (!ft_strncmp(data->prompt, "cd", 2))
			// 	cd(data, data->commands->args);
			// else if (!ft_strncmp(data->prompt, "pwd", 3))
			// 	pwd(data->commands->args);
			// else if (!ft_strncmp(data->prompt, "env", 3))
			// 	env(data, data->commands->args);
			// else if (!ft_strncmp(data->prompt, "export", 6))
			// 	exporc(data, data->commands->args);
			// else if (!ft_strncmp(data->prompt, "unset", 5))
			// 	unset(data, data->commands->args);
			// else if (!ft_strncmp(data->prompt, "exit", 4))
			// 	ixit(data, data->commands->args);
			// else if (!ft_strncmp(data->prompt, "boucle", 4))
			// {
			// 	signal(SIGINT, SIG_DFL);
			// 	while (1)
			// 	{
			// 		printf("debug\n");
			// 	}
			// 	signal(SIGINT, replace_sig_int);
			// }
		}
		free_data_struct(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	// if (!isatty(0))
	// 	return (write(2, "t nul\n" ,6), -1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, replace_sig_int);
	g_exit_status = 0;
	initialize_data(&data, envp);
	// minishell(&data);
	minishell_test(&data, av);
	if (data.start_env)
		free_lexer_struct(&data.start_env);
	free_data_struct(&data);
	return (0);
}
