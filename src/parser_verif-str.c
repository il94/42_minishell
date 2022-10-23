/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verif-str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:36 by auzun             #+#    #+#             */
/*   Updated: 2022/10/23 11:59:05 by auzun            ###   ########.fr       */
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
			if (only_dir)
				new = ft_lstnew_lex(ft_strjoin(dir->d_name, "/"));
			else
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

t_lex	*lst_of_occurrences(t_data *data, char *path, t_lex *to_find, int dir_only)
{
	t_lex	*r_value;
	t_lex	*dir_file;
	t_lex	*tmp;

	if (dir_only)
		r_value = send_dir_content(path, data, 1);
	else
		r_value = send_dir_content(path, data, 0);
	if (!dir_file || !to_find)
		return (NULL);
	dir_file = r_value;
	while (dir_file)
	{
		if (!aplly_star(to_find, *dir_file))
		{
			if (!dir_file->prev)
				r_value = r_value->next;
			tmp = dir_file->next;
			ft_lstdelone_lex(dir_file);
			dir_file = tmp;
		}
		else
			dir_file = dir_file->next;
	}
	return (r_value);
}

/*int test_apply(char *find)
{
	t_data *test;
	t_lex	*ls;
	t_lex	*to_find;

	printf("%s", GREEN);
	ft_lstprint_lex(lst_of_occurrences(test, ".", ft_lstsplit_charset_lex(find, "*")));
	
	return 0;
}*/

/*on a l'addresse du paths qu'on va modif*/
t_lex	*find_occurrences(t_data *data, t_lex *paths)
{
	int		index;
	int		index2;
	char	*path;
	char	*to_find;

	index = -1;
	index2 = 0;
	path = malloc(ft_strlen(paths->str) * sizeof(char));
	to_find = malloc(ft_strlen(paths->str) * sizeof(char));
	while (paths->str[++index] && paths->str[index] != '*')
		path[index] = paths->str[index];
	path[index] = paths->str[index];
	*(path + (index +1)) = '\0';
	if (path[index] == '*')
	{
		while (index >= 0 && path[index] != '/')
			path[index--] = '\0';
		if (index >= 0 && path[index] == '/')
			index++;
	}
	if (index >= 0)
	{
		while (paths->str[index] && !is_there("/", paths->str[index]))
			to_find[index2++] = paths->str[index++];
		to_find[index2] = '\0';
	}
	if (paths->str[index] && (paths->str[index] == '/') && to_find)
		return (lst_of_occurrences(data, path, ft_lstsplit_charset_lex(to_find, "*"), 1));
	else
		return (lst_of_occurrences(data, path, ft_lstsplit_charset_lex(to_find, "*"), 0));
}

char	*concate_paths(char *path, char *finded)
{
	int		index;
	char	*rvalue;
	char	*new_path;

	index = 0;
	new_path = malloc((ft_strlen(path) + 1) * sizeof(char));
	if (!new_path)
		return (NULL);
	while (path && *path && *path != '*')
		new_path[index++] = *(path++);
	new_path[index++] = *path;
	new_path[index--] = '\0';
	if (new_path[index] == '*')
	{
		while (index >= 0 && new_path[index] != '/')
			new_path[index--] = '\0';
	}
	rvalue = ft_strjoin(new_path, finded);
	free(new_path);
	if (!rvalue)
		return (NULL);
	while (*path && *path != '/')
		path++;
	if (!path)
		return (rvalue);
	rvalue = ft_strjoin(rvalue, path);
	if (!rvalue)
		return (NULL);
	return (rvalue);
}

t_lex	*wildiwonkard(t_data *data, char *path)
{
	t_lex	*paths;
	t_lex	*lst;
	t_lex	*new;
	char	*str;
	
	paths = ft_lstnew_lex(ft_strdup("./s*/"));
	lst = find_occurrences(data, paths);
	ft_lstprint_lex(lst);
	/*paths = ft_lstnew_lex(ft_strdup(path));
	while (paths)
	{
		if (ft_strchr(paths->str, '*'))
			lst = find_occurrences(data, paths);
		while (lst)
		{
			str = concate_paths(paths->str, lst->str);
			if (!str)
				free_all_and_exit(data, "malloc");
			new = ft_lstnew_lex(str);
			if (!new)
				free_all_and_exit(data, "malloc");
			ft_lstadd_back_lex(&paths, new);
			lst = lst->next;
		}
		if (lst)
		{
			new = paths->next;
			ft_lstdelone_lex(paths);
			paths = new;
			new = NULL;
			ft_lstclear_lex(&lst);
			lst = NULL;
		}
		if (paths && !ft_strchr(paths->str, '*'))
			paths = paths->next;
	}*/
	return (paths);
}

/*int test_apply(char *find)
{
	t_data *test;
	t_lex	*ls;
	t_lex	*to_find;

	printf("%s", GREEN);
	ft_lstprint_lex(lst_of_occurrences(test, ".", ft_lstsplit_charset_lex(find, "*")));
	
	return 0;
}*/

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