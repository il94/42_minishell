/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/17 19:48:57 by auzun            ###   ########.fr       */
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
t_redi	    define_redi(t_lex *element);
t_delimiter	get_delimiter(t_lex *element);
int			is_token(t_lex *element, char *c, char *charset);
int			is_there(char *str, char in);

/* lexer_initialize.c */
int		search_closing_quote(t_lex *lexer, char *quote);
int		concat_quotes(t_lex **lexer);
int		concat_tokens(t_lex **lexer);
int		concat_env_variable(t_lex **lexer);
int		concat_lexer(t_data *data);
void	get_lexer(t_data *data);

/* lexer.c */
void	define_delimiter(t_data *data);
void	lexer(t_data *data);

/* minishell.c */
void	minishell(t_data *data);

/* free_memory.c */
void	free_lexer_struct(t_lex **lexer);
void	free_fd_struct(t_fd **list);
void	free_command_struct(t_cmd **commands);
void	free_data_struct(t_data *data);
void	free_all_and_exit(t_data *data, char *str_error);

/* initialize.c */
void	initialize_data(t_data *data);

/* main.c */
int		main(int ac, char **av, char **envp);

#endif