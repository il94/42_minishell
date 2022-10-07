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

# include "libft.h"

typedef enum e_delimiter
{
	NOTHING_D,
	PIPE,
	AND,
	OR,
	PIPE_D,
	P_OPENED,
	P_CLOSED
}	t_delimiter;

typedef enum e_redi
{
	NOTHING_R,
	L_CHEVRON,
	R_CHEVRON,
	L_DOUBLE_CHEVRON,
	R_DOUBLE_CHEVRON,
	PIPE_R,
}	t_redi;

typedef struct s_fd
{
	int			fd;
	char		*file;
	t_redi		operator;
	struct s_fd	*next;
}					t_fd;

typedef struct s_cmd
{
	// int				id;
	t_fd			*input;
	t_fd			*output;
	t_delimiter		delimiter;
	char			*command;
	char			**args;
	struct s_cmd	*child_cmd;
	struct s_cmd	*next;
}					t_cmd;

t_cmd		*ft_lstnew(void);
void		ft_lstclear(t_cmd **lst);
void		ft_lstadd_back(t_cmd **lst, t_cmd *new);
void		ft_lstdelone(t_cmd *lst);

// void		ft_lstadd_front(t_list **lst, t_list *new);
// int			ft_lstsize(t_list *lst);
// t_list		*ft_lstlast(t_list *lst);
// void		ft_lstiter(t_list *lst, void (*f)(void *));
// t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// int			ft_lstis_correct(t_list *lst, int size);
// void		ft_lstprint(t_list *lst);
// t_list		*ft_lstsplit_charset(char const *s, char *charset);

#endif