/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verif-str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:36 by auzun             #+#    #+#             */
/*   Updated: 2022/10/22 13:31:17 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include "../include/minishell.h"

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"



/* let us make a recursive function to print the content of a given folder */

t_lex   *send_dir_content(char *path, t_data *data, int only_dir)
{
	t_lex			*ls;
	t_lex			*new;
	DIR				*d;
	struct dirent	*dir;// for the directory entries

	ls = NULL;
	d = opendir(path); // open the path
	if(d == NULL) 
		return (NULL); // if was not able, return
	dir = readdir(d);
	if (!dir)
		return (NULL);
	while (dir) // if we were able to read somehting from the directory
	{
		if (!only_dir | (only_dir && dir->d_type == DT_DIR))
		{
			new = ft_lstnew_lex(ft_strdup(dir->d_name));
			if (!new || !new->str)
			{
				closedir(d);
				free_lexer_struct(&ls);
				free_all_and_exit(data, "malloc");
			}
			ft_lstadd_back_lex(&ls, new);
		}
		dir = readdir(d);
	}
	closedir(d); // finally close the directory
	return (ls);
}

int	aplly_star(t_lex *to_find, t_lex dir_file)
{
	int	index;
	int	in_star;

	if (ft_strlen(dir_file.str) < ft_strlen(to_find->str))
		return (0);
	index = 0;
	in_star = 0;
	while (to_find)
	{
		if (index >= ft_strlen(dir_file.str))
			return (0);
		if(!ft_strncmp(dir_file.str + index, to_find->str, ft_strlen(to_find->str)))
		{
			if (!to_find->next && ft_strcmp(dir_file.str + index, to_find->str))
				return (0);
			index += ft_strlen(to_find->str);
			to_find = to_find->next;
			in_star = 0;
		}
		else if(!strcmp(to_find->str, "*"))
		{
			to_find = to_find->next;
			index +=1;
			in_star = 1;
		}
		else if(in_star)
			index += 1;
		else if(!in_star)
			return (0);
	}
	return (1);
}

int test_apply(char *find)
{
	t_data *test;
	t_lex	*ls;
	t_lex	*to_find;

	ls = send_dir_content("src/.", test, 0);
	ft_lstprint_lex(ls);
	printf("================\n");
	to_find = ft_lstsplit_charset_lex(find, "*");
	ft_lstprint_lex(to_find);
	printf("================\n");
	while (ls)
	{
		if (aplly_star(test, ls, to_find, *ls))
		{
			printf("\n %s IS THERE YOUHOUUUUUU  %s \n", GREEN, ls->str);
		}
		ls = ls->next;
	}
	
	return 0;
}

char	*find_occurrence(t_data *data, char *path, t_lex *str, t_lex *ls, int only_dir)
{
	t_lex	*dir_content;
	t_lex	*split_star;

	if (path == NULL)
		*path = '.';
	dir_content = send_dir_content(path, data, only_dir);
	if (!dir_content)
		return (NULL);
	split_star = ft_lstsplit_charset_lex(str, "*");
	if (!split_star)
	{
		free(path);
		free_lexer_struct(&split_star);
		free_lexer_struct(&str);
		free_lexer_struct(&ls);
		free_all_and_exit(data, "malloc");
	}
	while (dir_content)
	{
		if (aplly_star(str->str, *dir_content))
			
	}
}

t_lex	*wildiwonkard(t_data *data, char *str)
{
	t_lex	*ls;
	t_lex	*path_split;
	char	*path;

	path_split = ft_lstsplit_charset_lex(str, "/");
	path = NULL;
	if (!path_split)
		free_all_and_exit(data, "malloc");
	while (path_split)
	{
		if (strcmp(path_split->str, ".") && strcmp(path_split->str, "..")
			&& strcmp(path_split->str, "/") && ft_strchr(path_split->str, '*'))
			{
				if (path_split->next->str[0] == '/')
					
				else
			}
		
		path = ft_strjoin(path, path_split->str);
		if (!path)
			free_all_and_exit(data, "malloc");
		path_split = path_split->next;
	}
	return (ls);
	/*if (!strcmp(str, '*'))
		return (send_dir_content(".", data));*/
}

// void show_dir_content(char * path)
// {
//   DIR * d = opendir(path); // open the path
//   if(d==NULL) return; // if was not able, return
//   struct dirent * dir; // for the directory entries
//   while ((dir = readdir(d)) != NULL) // if we were able to read somehting from the directory
//     {
//       if(dir-> d_type != DT_DIR) // if the type is not directory just print it with blue color
//         printf("%s%s\n",BLUE, dir->d_name);
//       else
//       if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
//       {
//         printf("%s%s\n",GREEN, dir->d_name); // print its name in green
//         char d_path[255]; // here I am using sprintf which is safer than strcat
//         printf(d_path, "%s/%s", path, dir->d_name);
//         //show_dir_content(d_path); // recall with the new path
//       }
//     }
//     closedir(d); // finally close the directory
// }

/*int main(int argc, char **argv)
{
  printf("%s\n", NORMAL_COLOR);
  show_dir_content(argv[1]);
  printf("%s\n", NORMAL_COLOR);
  return(0);
}*/