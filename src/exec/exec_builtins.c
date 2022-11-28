/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilandols <ilandols@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:13:17 by auzun             #+#    #+#             */
/*   Updated: 2022/11/28 13:36:13 by ilandols         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	return (0);
}

int	builtins_parent(t_data *data, t_cmd *cmd)
{
	if (!cmd->command)
		return (0);
	if (!ft_strcmp(cmd->command, "export"))
		return (exporc(data, cmd->args->next));
	else if (!ft_strcmp(cmd->command, "unset"))
		return (unset(data, cmd->args->next));
	else if (!ft_strcmp(cmd->command, "exit"))
		return (ixit(data, cmd->args->next));
	else if (!ft_strcmp(cmd->command, "cd"))
		return (cd(data, cmd->args->next));
	return (0);
}

int	builtins_child(t_data *data, t_cmd *cmd)
{
	if (!cmd->command)
		return (0);
	if (!ft_strcmp(cmd->command, "env"))
		return (env(data, cmd->args->next));
	else if (!ft_strcmp(cmd->command, "pwd"))
		return (pwd(cmd->args->next));
	else if (!ft_strcmp(cmd->command, "echo"))
		return (echo(cmd->args->next));
	return (0);
}