/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:26:57 by auzun             #+#    #+#             */
/*   Updated: 2022/12/01 15:12:39 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_command(t_data *data, t_cmd *command)
{
	char	**args;
	char	**envp;

	if (!check_cmd_and_fds(data, command))
		return ;
	dup2_r_and_w(command->input, command->output);
	close_all_fd(data->commands);
	if (is_builtin(command->command))
		builtins_child(data, command);
	else
	{
		envp = get_env_in_array(data);
		args = get_args_in_array(data, command->args, envp);
		if (execve(command->command, args, envp))
			cmd_error(errno, command->command);
		if (envp)
			ft_free_array(envp);
		ft_free_array(args);
	}
}

int	red_light(t_data *data, t_cmd *command)
{
	if (command && (command->prev && (command->prev->delimiter == AND
				|| command->prev->delimiter == OR)))
	{
		wait_process(data->commands, &data->prev_exit_status);
		if (g_exit_status && command->prev->delimiter == AND)
			return (1);
		else if (!g_exit_status && command->prev->delimiter == OR)
			return (1);
		else if (g_exit_status && command->prev->delimiter == OR)
			g_exit_status = 0;
	}
	return (0);
}

void	green_light(t_data *data, t_cmd *command)
{
	command->pid = fork();
	if (command->pid == -1)
		free_all_and_exit(data, "fork");
	if (command->pid == 0)
	{
		exec_command(data, command);
		free_data_struct(data);
		if (data->start_env)
			free_lexer_struct(&(data->start_env));
		exit (g_exit_status);
	}
	else
		builtins_parent(data, command);
}

int	launch_command(t_data *data, t_cmd *command)
{
	if (red_light(data, command))
		return (0);
	green_light(data, command);
	close_fd(command);
	return (1);
}