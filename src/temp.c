/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:14:06 by ilandols          #+#    #+#             */
/*   Updated: 2022/11/25 23:27:54 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_cmd(t_cmd *commands, char *state)
{
	printf("==================%s=============\n", state);
	if (commands->input)
	{
		// printf("Input = %d", commands->input->operator);
		// printf("\n-----\n");
		printf("Input = ");
		ft_print_fd(commands->input);
		printf("\n-----\n");
	}
	if (commands->command)
	{		
		printf("Command = %s", commands->command);
		printf("\npid = %d", commands->pid);
		printf("\n-----\n");
	}
	if (commands->args)
	{
		printf("Args = \n");
		ft_lstprint_lex(commands->args);
		printf("-----\n");
	}
	if (commands->output)
	{
		// printf("Output = %d", commands->output->operator);
		// printf("\n-----\n");
		printf("Output = ");
		ft_print_fd(commands->output);
		printf("\n-----\n");
	}
	if (commands->delimiter)
	{
		printf("Delimiter = %d", commands->delimiter);
		printf("\n-----\n");
	}
	if (commands->child_cmd)
		print_cmd(commands->child_cmd, "CHILD");
	printf("==================END %s=============\n", state);
	if (commands->next)
		print_cmd(commands->next, state);
}

void	ft_print_fd(t_fd *fd)
{
	while (fd)
	{
		printf("[%d] {%s} {fd = %d} | ", fd->operator, fd->file, fd->fd);
		fd = fd->next;
	}
}
