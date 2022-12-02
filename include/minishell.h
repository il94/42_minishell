/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/02 16:44:44 by ilandols         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

extern int	g_exit_status;

/*============================================================================*/

/* builtins_cd.c */
void	cd_modify_pwd_values(t_data *data);
void	cd(t_data *data, t_lex *args);

/* builtins_echo.c */
int		echo_detect_n_flag(t_lex *args);
void	echo(t_lex *args);

/* builtins_export.c */
void	exporc_normal_mode(t_data *data, t_lex *arg, int i);
void	exporc_append_mode(t_data *data, t_lex *arg, int i);
int		exporc_parsing_argument(t_lex *arg, int i);
void	exporc(t_data *data, t_lex *arg);

/* builtins.c */
void	pwd(t_data *data);
void	env(t_data *data);
void	unset(t_data *data, t_lex *args);
void	ixit(t_data *data, t_lex *args);

/*============================================================================*/

/* exec_builtins.c */
int		is_builtin_parent(char *cmd);
int		is_builtin(char *cmd);
void	builtins_parent(t_data *data, t_cmd *cmd);
void	builtins_child(t_data *data, t_cmd *cmd);

/* exec_launch_command_utils.c */
char	**get_env_in_array(t_data *data);
char	**get_args_in_array(t_data *data, t_lex *lst_args, char **free_if_l);
int		check_cmd_and_fds(t_data *data, t_cmd *command);

/* exec_launch_command.c */
void	exec_command(t_data *data, t_cmd *command);
int		red_light(t_data *data, t_cmd *command);
void	green_light(t_data *data, t_cmd *command);
int		launch_command(t_data *data, t_cmd *command);

/* exec_redir.c */
int		verif_files_fd(t_fd *in, t_fd *out);
void	dup2_r_and_w(t_fd *in, t_fd *out);
void	close_fd(t_cmd *command);
void	close_all_fd(t_cmd *command);

/* exec_wait.c */
void	wait_process(t_cmd *commands, int *prev_exit_status);

/* exec.c */
void	exec(t_data *data, t_cmd *commands);

/*============================================================================*/

/* lexer_argument.c */
int		define_argument(t_data *data);

/* lexer_child.c */
int		define_child(t_data *data);

/* lexer_command.c */
int		define_command(t_data *data);

/* lexer_delimiter.c */
void	define_delimiter(t_data *data);

/* lexer_initialize_utils.c */
int		concat_element(t_lex **lexer, t_bool is_prev);
int		search_closing_quote(t_lex *lexer);
int		search_closing_parenthese(t_lex *lexer);

/* lexer_initialize.c */
int		concat_lexer(t_data *data);

/* lexer_redi.c */
int		define_redi(t_data *data);

/* lexer_utils.c */
int		is_token(t_lex *element);
t_redi	get_redi(t_lex *element);
t_deli	get_delimiter(t_lex *element);

/* lexer.c */
void	get_lexer(t_data *data);
void	lexer(t_data *data);

/*============================================================================*/

/* parser_check_str.c */
t_lex	*check_str(t_data *data, char *str);

/* parser_cmd_arg.c */
t_lex	*parsing_cmd(t_data *data, t_cmd *command, char *cmd);
void	parser_cmd_arg(t_data *data, t_cmd *cmd);

/* parser_dir_utils.c */
char	*concate_paths(char *path, char *finded);

/* parser_dir.c */
t_lex	*send_dir_content(char *path, int only_dir, int *err);

/* parser_expand_utils.c */
char	*expand(char *to_find, t_lex *env);
char	*return_env_var(t_data *data, char *str, int *index, char **tmp);

/* parser_expand.c */
char	*add_unsuspect_char(char *last, char *next, int *index, int *quotes);
char	*check_expand(t_data *data, char **str, int quotes, int n);

/* parser_ft_expand.c */
char	*cut_there(char *str, int start, int end);
t_lex	*create_new_el(char *str, int *start, int *end);
void	add_new_el_to_lst(t_data *data, t_lex **new, t_lex **lst, char *str);
t_lex	*split_str(t_data *data, char *str);
t_lex	*ft_expand(t_data *data, char *str);

/* parser_ft_put_in_quotes.c */
int		other_quote(char c);
void	verif_quotes_closed(int quotes, int j, char *rvalue, char *name);
char	*put_in_quotes(char *name, int i, int j, int quotes);

/* parser_ft_take_off_quotes.c */
char	*take_off_quotes(char *str);

/* parser_ft_wildcard.c */
t_lex	*ft_wildcard(t_data *data, t_lex *path, t_lex *lst_str);

/* parser_get_paths.c */
void	get_all_paths(t_data *data);

/* parser_here_doc.c */
void	generate_here_doc(t_data *data, t_fd *file);

/* parser_input_output.c */
int		parser_input_output(t_data *data, t_cmd *cmd);

/* parser_open_files.c */
void	open_files(t_data *data, t_cmd *cmd);

/* parser_pipe.c */
void	generate_pipe(t_data *data, t_fd *file, t_cmd *cmd);

/* parser_wildcard_algo.c */
int		aplly_star(t_lex *to_find, t_lex dir_file, int index, int in_star);

/* parser_wildcard_utils.c */
t_lex	*find_occurrences(t_lex *paths, int *err);

/* parser_wildcard.c */
t_lex	*wildiwonkard(t_data *data, t_lex *path, t_lex *lst_str);

/* parser_utils.c */
int		is_there_in_out(t_cmd *cmd);

/* parser.c */
void	parser(t_data *data, t_cmd *command, int is_child);

/*============================================================================*/

/* error.c */
int		msg_error(char *err);
void	cmd_error(int status, char *cmd);
void	define_exit_status(char *to_print, int error_code);

/* free_memory.c */
void	free_lexer_struct(t_lex **lexer);
void	free_fd_struct(t_fd **list);
void	free_command_struct(t_cmd **commands);
void	free_data_struct(t_data *data);
void	free_all_and_exit(t_data *data, char *str_error);

/* initialize.c */
void	initialize_data(t_data *data, char **envp);

/* is_there.c */
int		is_there(char *str, char in);
int		is_there_v2(char *is, char *there);
int		is_there_wildcard(char *str);
int		is_there_el_outside_quotes(char *str, char el);
int		is_there_el_outside_quotes_v2(char *str, char *el);

/* signals.c */
void	replace_sig_quit(int signum);
void	replace_sig_int_exe(int signum);
void	sig_unexpected_eof(char *delimiter);
void	sig_int_heredoc_child(int signum);
void	sig_int_heredoc_parent(int signum);
void	replace_sig_int(int signum);

/* utils.c */
char	*get_deli_char(t_deli r);
int		is_in_quotes(char *start, char *now);
int		is_dir(char *path);

/*============================================================================*/

/* minishell.c */
void	read_prompt(t_data *data);
void	minishell(t_data *data);

/* main.c */
int		main(int ac, char **av, char **envp);

void	ft_print_fd(t_fd *fd);
void	print_cmd(t_cmd *commands, char *state);

#endif
