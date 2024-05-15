/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:31:08 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/13 22:31:59 by caqueiro         ###   ########.fr       */
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
	args = (char **)ft_calloc(size + 2, sizeof (char *));
	i = 0;
	args[i++] = cmd->instruction;
	if (cmd->flags)
	{
		current = cmd->flags->head;
		while (current)
		{
			args[i++] = current->value;
			current = current->next;
		}
	}
	if (cmd->args)
	{
		current = cmd->args->head;
		while (current)
		{
			args[i++] = current->value;
			current = current->next;
		}
	}
	args[i] = NULL;
	return (args);
}