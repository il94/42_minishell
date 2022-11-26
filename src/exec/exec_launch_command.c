/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_launch_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:26:57 by auzun             #+#    #+#             */
/*   Updated: 2022/11/26 21:18:25 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_command(t_data *data, t_cmd *command)
{
	char	**args;
	char	**envp;

	if (!check_cmd_and_fds(command))
		return ;
	dup2_r_and_w(command->input, command->output);
	close_all_fd(data->commands);
	if (is_builtin(command->command))
		builtins_child(data, command);
	else
	{
		envp = get_env_in_array(data);
		args = get_args_in_array(data, command->args, envp);
		execve(command->command, args, envp);
		if (envp)
			ft_free_array(envp);
		ft_free_array(args);
	}
}

int	red_light(t_data *data, t_cmd *command)
{
	if ((command->prev && (command->prev->delimiter == AND
			|| command->prev->delimiter == OR)))
	{
		wait_process(data->commands);
		if (g_exit_status && command->prev->delimiter == AND)
			return (1);
		else if (!g_exit_status && command->prev->delimiter == OR)
				return (1);
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
		signal(SIGINT, SIG_DFL);
		exec_command(data, command);
		free_data_struct(data);
		if (data->start_cmd)
			free_lexer_struct(&(data->start_env));
		exit (0);
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