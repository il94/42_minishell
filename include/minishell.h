/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:43:09 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/28 19:55:57 by auzun            ###   ########.fr       */
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

/* temp.c */
void	ft_print_fd(t_fd *fd);
void	print_cmd(t_cmd *commands, char *state);
char	*expand(char *to_find, t_lex *env);
void	replace_sig_int(int signum);
void	sig_int_heredoc_child(int signum);
void	sig_int_heredoc_parent(int signum);
void	replace_sig_quit(int signum);

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
int		is_dir(char *path);
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
void	generate_pipe(t_data *data, t_fd *file, t_cmd *cmd);
void	open_files(t_data *data, t_cmd *cmd);


/*expand*/
char	*check_expand(t_data *data, char **str, int quotes, int index);
char	*expand(char *to_find, t_lex *env);
char	*return_env_var(t_data *data, char *str, int *index, char **tmp);

/* parser.c */
void	parser(t_data *data, t_cmd *command, int is_child);
void	parser_input_output(t_data *data, t_cmd *cmd);
void	parser_cmd_arg(t_data *data, t_cmd *cmd);
t_lex	*check_str(t_data *data, char *str);
t_lex	*ft_wildcard(t_data *data, t_lex *path, t_lex *lst_str);
t_lex	*ft_expand(t_data *data, char *str);
char	*take_off_quotes(char *str);
t_lex	*split_str(t_data *data, char *str);
char	*put_in_quotes(char *name, int i, int j, int quotes);
//void	parser(t_data *data);

/* parser_here_doc.c */
void	generate_here_doc(t_data *data, t_fd *file);

/*exec_redir.c*/
void	dup2_r_and_w(t_fd *in, t_fd *out);
void	close_all_fd(t_cmd *command);
void	close_fd(t_cmd *command);
int		verif_files_fd (t_fd *in, t_fd *out);

/*exec_wait.c*/
int 	wait_process(t_cmd *commands, int *prev_exit_status);

/*exec_builtins.c*/
int		builtins_parent(t_data *data, t_cmd *cmd);
int		builtins_child(t_data *data, t_cmd *cmd);
int		is_builtin(char *cmd);

/*exec_launch_command_utils.c*/
char	**get_env_in_array(t_data *data);
char	**get_args_in_array(t_data *data, t_lex *lst_args, char **free_if_l);
int		check_cmd_and_fds(t_data *data, t_cmd *command);

/*exec_launch_command.c*/
int	launch_command(t_data *data, t_cmd *command);

/* exec.c */
void	exec(t_data *data, t_cmd *commands);

/* minishell.c */
void	minishell(t_data *data);

/* error.c */
int		msg_error(char *err);
void	cmd_error(int status, char *cmd);

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
