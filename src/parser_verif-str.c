/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verif-str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:34:36 by auzun             #+#    #+#             */
/*   Updated: 2022/10/21 18:42:44 by auzun            ###   ########.fr       */
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

t_lex   *send_dir_content(char *path, t_data *data)
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
		new = ft_lstnew_lex(ft_strdup(dir->d_name));
		if (!new || !new->str)
		{
			closedir(d);
			free_lexer_struct(&ls);
			free_all_and_exit(data, "malloc");
		}
		ft_lstadd_back_lex(&ls, new);
		dir = readdir(d);
	}
	closedir(d); // finally close the directory
	return (ls);
}

t_lex	*wildiwonkard(t_data *data, char *str)
{
	t_lex	*ls;

	while (str)
	{
		/* code */
	}
	
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