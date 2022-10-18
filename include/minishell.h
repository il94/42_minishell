/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/18 19:28:25 by ilandols         ###   ########.fr       */
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
t_redi	get_redi(t_lex *element);
t_deli	get_delimiter(t_lex *element);

/* lexer_command.c */
int		define_command(t_data *data);

/* lexer_redi.c */
char	*find_file(t_data *data);
t_fd	*define_fd(t_data *data);
int		define_redi(t_data *data);

/* lexer_delimiter.c */
void	define_delimiter(t_data *data);

/* lexer.c */
void	get_lexer(t_data *data);
void	lexer(t_data *data);

/* lexer_initialize.c */
int		search_closing_quote(t_lex *lexer, char *quote);
int		concat_quotes(t_lex **lexer);
int		concat_tokens(t_lex **lexer);
int		concat_env_variable(t_lex **lexer);
int		concat_lexer(t_data *data);

/* minishell.c */
void	minishell(t_data *data);

/* utils.c */
int		is_there(char *str, char in);
char	*expand(char *to_find, t_lex *env);

/* free_memory.c */
void	free_lexer_struct(t_lex **lexer);
void	free_fd_struct(t_fd **list);
void	free_command_struct(t_cmd **commands);
void	free_data_struct(t_data *data);
void	free_all_and_exit(t_data *data, char *str_error);

/* initialize.c */
void	initialize_data(t_data *data, char **envp);

/* main.c */
int		main(int ac, char **av, char **envp);

#endif
