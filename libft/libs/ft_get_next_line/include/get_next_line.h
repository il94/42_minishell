/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:42:59 by ilandols          #+#    #+#             */
/*   Updated: 2022/12/01 13:58:01 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 5

int		while_get_next_line(char **line, char *buffer, int fd);
char	*ft_get_next_line(int fd);
int		ft_strchr_gnl(char *s, int c);
void	remove_last_line(char *buffer);
int		is_end_of_line(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	get_line(char *line, char *buffer);

#endif
