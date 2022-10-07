/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/07 12:29:46 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/* lexer.c */
void	lexer(t_cmd *commands, char *input);

/* minishell.c */
void	minishell(t_cmd *commands);

/* free_memory.c */
void	free_fd_struct(t_fd *list);
void	free_command_struct(t_cmd *commands);
void	free_all_and_exit(t_cmd *commands, char *str_error);

/* main.c */
int		main(int ac, char **av, char **envp);

#endif