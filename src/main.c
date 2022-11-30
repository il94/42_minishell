/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:42:47 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/30 15:05:25 by auzun            ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	// if (!isatty(0))
	// 	return (write(2, "t nul\n" ,6), -1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, replace_sig_int);
	g_exit_status = 0;
	initialize_data(&data, envp);
	minishell(&data);
	//minishell_test(&data, av);
	if (data.start_env)
		free_lexer_struct(&data.start_env);
	free_data_struct(&data);
	return (0);
}
