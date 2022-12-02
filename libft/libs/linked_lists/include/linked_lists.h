/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilyes@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:14:16 by ilandols          #+#    #+#             */
/*   Updated: 2022/09/01 00:14:16 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LISTS_H
# define LINKED_LISTS_H

# include "../../../include/libft.h"

typedef enum e_deli
{
	NOTHING_D,
	PIPE_D,
	AND,
	OR
}	t_deli;

typedef enum e_redi
{
	NOTHING_R,
	PIPE_R,
	L_CHEVRON,
	R_CHEVRON,
	L_DOUBLE_CHEVRON,
	R_DOUBLE_CHEVRON
}	t_redi;

typedef struct s_fd
{
	int			fd;
	char		*file;
	t_redi		operator;
	struct s_fd	*next;
	struct s_fd	*prev;
}					t_fd;

typedef struct s_lex
{
	char			*str;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	int				pid;
	t_fd			*input;
	char			*command;
	t_lex			*args;
	struct s_cmd	*child_cmd;
	t_fd			*output;
	t_deli			delimiter;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	int		parent_in_fd;
	int		parent_out_fd;
	int		prev_exit_status;
	char	*prompt;
	t_cmd	*commands;
	t_cmd	*start_cmd;
	t_lex	*lexer;
	t_lex	*start_lex;
	t_lex	*env;
	t_lex	*start_env;
}			t_data;

/* for t_fd */
void		ft_lstadd_back_fd(t_fd **lst, t_fd *new);
t_fd		*ft_lstnew_fd(void);

/* for t_cmd */
t_cmd		*ft_lstnew_cmd(void);
void		ft_lstclear_cmd(t_cmd **lst);
void		ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);

/* for t_lex */
char		**ft_lst_lex_to_array(t_lex *lst_lex);
t_lex		*ft_lstnew_lex_dup(char *str);
t_lex		*ft_lstnew_lex(char *str);
void		ft_lstclear_lex(t_lex **lst);
void		ft_lstadd_back_lex(t_lex **lst, t_lex *new);
t_lex		*ft_lstsplit_charset_lex(char const *s, char *charset);
int			ft_lstis_correct_lex(t_lex *lst, int size);
int			ft_lstsize_lex(t_lex *lst);
void		ft_lstprint_lex(t_lex *lst);
void		ft_lstdelone_lex(t_lex *lst);
t_lex		**first_el(t_lex **lst);
t_lex		**last_el(t_lex **lst);
t_lex		*ft_array_to_lst_lex(char **array);
t_lex		*ft_lststrncmp_lex(t_lex **lst, char *to_find, int n);
t_lex		*ft_lstlast_lex(t_lex *lst);
t_lex		*ft_lststrrncmp_lex(t_lex **lst, char *to_find);

// void		ft_lstadd_front(t_list **lst, t_list *new);
// t_list	*ft_lstlast(t_list *lst);
// void		ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
