/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:11:29 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/26 23:23:14 by auzun            ###   ########.fr       */
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

static void	get_paths(t_data *data, t_cmd *command, char **bin_paths)
{
	t_cmd	*cmd;

	cmd = command;
	while (bin_paths && cmd)
	{
		if (cmd->child_cmd)
			get_paths(data, cmd->child_cmd, bin_paths);
		if (cmd->command && !is_builtin(cmd->command))
		{
			cmd->command = get_command_path(cmd->command, bin_paths);
			if (!cmd->command)
			{
				ft_free_array(bin_paths);
				free_all_and_exit(data, "malloc");
			}
		}
		cmd = cmd->next;
	}
}

void	get_all_paths(t_data *data)
{
	char	**bin_paths;

	bin_paths = get_bin_paths(data);
	get_paths(data, data->start_cmd, bin_paths);
	if (bin_paths)
		ft_free_array(bin_paths);
}
