/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__get_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/22 14:19:43 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_command_path(char *path, char **bin_paths)
{
	char	*command_path;
	int		i;

	i = 0;
	while (!ft_strchr(path, '/') && ft_strlen(path) > 0 && bin_paths[i])
	{
		command_path = ft_pathjoin(bin_paths[i], path);
		if (!command_path)
		{
			free(path);
			return (NULL);
		}
		if (access(command_path, X_OK) == 0)
		{
			free(path);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	return (path);
}

char	**get_bin_paths(t_data *data)
{
	char	**bin_paths;
	t_lex	*paths;

	bin_paths = NULL;
	paths = ft_lststrncmp_lex(&data->env, "PATH=", 5);
	if (paths)
	{
		bin_paths = ft_split(&paths->str[5], ':');
		if (!bin_paths)
			free_all_and_exit(data, "malloc");
	}
	return (bin_paths);
}

void	get_all_paths(t_data *data)
{
	char	**bin_paths;
	int		i;

	bin_paths = get_bin_paths(data);
	i = 0;
	while (bin_paths && data->commands)
	{
		data->commands->command = get_command_path(data->commands->command, bin_paths);
		if (!data->commands->command)
		{
			ft_free_array(bin_paths);
			free_all_and_exit(data, "malloc");
		}
		data->commands = data->commands->next;
	}
	data->commands = data->start_cmd;
	if (bin_paths)
		ft_free_array(bin_paths);
}
