/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/22 16:54:14 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TOKENS "<>|&"
# define QUOTES "\"\'"

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>


extern int	g_exit_status;

/* temp.c */
void	ft_print_fd(t_fd *fd);
void	print_cmd(t_cmd *commands, char *state);
char	*expand(char *to_find, t_lex *env);

/*============================================================================*/

/* builtins_env.c */
int		exporc_normal_mode(t_data *data, t_lex *args, int i);
int		exporc_append_mode(t_data *data, t_lex *args, int i);
int		exporc(t_data *data, t_lex *args);
int		unset(t_data *data, t_lex *args);

/* builtins.c */
int		echo_detect_n_flag(t_lex *args);
int		echo(t_lex *args);
void	cd_modify_pwd_values(t_data *data);
int		cd(t_data *data, t_lex *args);
int		pwd(t_lex *args);
int		env(t_data *data, t_lex *args);
int		ixit(t_data *data, t_lex *args);

/*============================================================================*/

/* lexer_utils.c */
int		concat_element(t_lex **lexer, t_bool is_prev);
int		is_token(t_lex *element);
t_redi	get_redi(t_lex *element);
t_deli	get_delimiter(t_lex *element);
int		search_closing_quote(t_lex *lexer, char *quote);
int 	search_closing_parenthese(t_lex *lexer);

/* lexer_child.c */
int		define_child(t_data *data);

/* lexer_command.c */
int		define_command(t_data *data);

/* lexer_argument.c */
int	    define_argument(t_data *data);

/* lexer_redi.c */
char	*find_file(t_data *data);
t_fd	*define_fd(t_data *data);
int		define_redi(t_data *data);

/* lexer_delimiter.c */
void	define_delimiter(t_data *data);

/* lexer_initialize.c */
int		concat_ampersand(t_lex **lexer);
int		concat_quotes(t_lex **lexer);
int		concat_tokens(t_lex **lexer);
int		concat_env(t_lex **lexer);
int		concat_lexer(t_data *data);

/* lexer.c */
void	get_lexer(t_data *data);
void	lexer(t_data *data);

/*============================================================================*/

/*dir utils*/
t_lex	*send_dir_content(char *path, int only_dir, int *err);
char	*concate_paths(char *path, char *finded);

/*wildcard*/
t_lex	*wildiwonkard(t_data *data, t_lex *path, t_lex *lst_str);
t_lex	*find_occurrences(t_lex *paths, int *err);
int		aplly_star(t_lex *to_find, t_lex dir_file, int index, int in_star);

/* parser_get_paths.c */
char	*get_command_path(char *path, char **bin_paths);
char	**get_bin_paths(t_data *data);
void	get_all_paths(t_data *data);

/* parser_open_files.c */
void    open_files(t_data *data, t_cmd *cmd);


/*expand*/
char	*check_expand(t_data *data, char **str, int quotes, int index);
char	*expand(char *to_find, t_lex *env);

/* parser.c */
void	parser(t_data *data, t_cmd *command);
void	parser_input_output(t_data *data, t_cmd *cmd);
void	parser_cmd_arg(t_data *data, t_cmd *cmd);
t_lex	*check_str(t_data *data, char *str);
t_lex	*ft_wildcard(t_data *data, t_lex *path, t_lex *lst_str);
t_lex	*ft_expand(t_data *data, char *str);
char	*take_off_quotes(char *str);
t_lex	*split_str(t_data *data, char *str);
char	*put_in_quotes(char *name, int i, int j, int quotes);
//void	parser(t_data *data);


/* minishell.c */
void	minishell(t_data *data);

/* error.c */
int		msg_error(char *err);

/* utils.c */
char	*get_deli_char(t_deli r);
int		is_there_el_outside_quotes_v2(char *str, char *el);
int		is_there_v2(char *is, char *there);
void	define_exit_status(char *to_print, int error_code);
int		is_there_el_outside_quotes(char *str, char el);
int		is_there_wildcard(char *str);
int		is_in_quotes(char *start, char *now);
int		is_there(char *str, char in);

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
