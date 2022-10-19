/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzun <auzun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:32:14 by ilandols          #+#    #+#             */
/*   Updated: 2022/10/19 18:49:36 by auzun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_there(char *str, char in)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (in == str[i])
			return (str[i]);
		i++;
	}
	return (0);
}

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