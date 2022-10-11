/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/11 22:31:32 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/* lexer_utils.c */
t_delimiter	define_delimiter(t_lex *element);
int			is_token(t_lex *element, char *c, char *charset);
int			is_there(char *str, char in);

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