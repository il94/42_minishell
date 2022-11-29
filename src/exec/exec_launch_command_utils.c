/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch_command_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:52:30 by auzun             #+#    #+#             */
/*   Updated: 2022/11/29 20:12:38 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env_in_array(t_data *data)
{
	char	**envp;

	envp = NULL;
	if (data->start_env)
	{
		envp = ft_lst_lex_to_array(data->start_env);
		if (!envp)
			free_all_and_exit(data, "malloc");
	}
	return (envp);
}

char	**get_args_in_array(t_data *data, t_lex *lst_args, char **free_if_l)
{
	char	**args;

	args = ft_lst_lex_to_array(lst_args);
	if (!args)
	{
		ft_free_array(free_if_l);
		free_all_and_exit(data, "malloc");
	}
	return (args);
}

static int	check_cmd(t_data *data, t_cmd *cmd)
{
	t_lex	*bin_paths;

	if (is_builtin(cmd->command))
		return (1);
	bin_paths = ft_lststrncmp_lex(&data->env, "PATH=", 5);
	if(cmd->command && !ft_strcmp(cmd->command, "."))
		g_exit_status = 2;
	else if (bin_paths && cmd->command && !ft_strcmp(cmd->command, ".."))
		g_exit_status = 2;
	else if (cmd->command && is_dir(cmd->command))
		g_exit_status = 126;
	else if (cmd->command && bin_paths
			&& (!ft_strchr(cmd->command, '/')
				|| access(cmd->command, X_OK)))
			g_exit_status = 127;
	else if(cmd->command && !bin_paths
			&& (!ft_strchr(cmd->command, '/')
				|| access(cmd->command, X_OK)))
			g_exit_status = 1;
	else
		return (1);
	return (0);
}

int	check_cmd_and_fds(t_data *data, t_cmd *command)
{
	if (!verif_files_fd(command->input, command->output))
	{
		g_exit_status = 1;
		return (0);
	}
	if (!command->command)
		return (0);
	if (!check_cmd(data, command))
		return (0);
	return (1);
}