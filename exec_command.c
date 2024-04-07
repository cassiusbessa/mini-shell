/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/04/07 16:27:56 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_size(t_command *cmd)
{
	int	size;

	if (!cmd)
		return (0);
	size = 0;
	if (cmd->args)
		size += cmd->args->size;
	if (cmd->flags)
		size += cmd->flags->size;
	return (size);
}
char	**list_to_args(t_command *cmd)
{
	char		**args;
	int			size;
	int			i;
	t_node		*current;

	size = args_size(cmd);
	if (!cmd || !size)
		return (NULL);
	current = cmd->flags->head;
	i = 0;
	args = ft_calloc(size + 2, sizeof (char *));
	args[i] = cmd->instruction;
	i++;
	while (current && i <= cmd->flags->size)
	{
		args[i] = current->value;
		current = current->next;
		i++;
	}
	current = cmd->args->head;
	while (current && i < cmd->flags->size + cmd->args->size)
	{
		args[i] = current->value;
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	print_double_pointer(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		i++;
	}
	ft_printf("\n");
}

void	exec_command(t_command *cmd)
{
	char	**args;
	if (!cmd)
		return ;
	args = list_to_args(cmd);
	print_double_pointer(args);
	execve("/usr/bin/ls", args, NULL);
	free(args);
}