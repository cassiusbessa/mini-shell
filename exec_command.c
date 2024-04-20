/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/04/20 20:25:19 by caqueiro         ###   ########.fr       */
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

void	exec_command(t_command *cmd)
{
	char	**args;
	if (!cmd)
		return ;
	args = list_to_args(cmd);
	set_cmd_path(cmd);
	execve(cmd->path, args, NULL);
	free(args);
}

void	exec_all_commands(t_cmd_lst *lst)
{
	t_command	*current;
	pid_t		pid;
	int			fd[2];

	if (pipe(fd) == -1)
		return ;
	current = lst->head;
	while (current)
	{
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			if (current->next)
				dup2(fd[1], 1);
			else
				dup2(1, fd[1]);
			exec_command(current);
			exit(1);
		}
		else
			waitpid(pid, NULL, 0);
		current = current->next;
	}
	close(fd[1]);
}