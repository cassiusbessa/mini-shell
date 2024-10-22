/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:55:10 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 21:00:00 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_last_status(t_hashmap *envs, int status);

void	pre_exec(t_token_lst *lst)
{
	unquotes_all_words(lst);
	pipe_all_cmds(lst);
	redir_all_cmds(lst);
}

void	update_status(int status, t_hashmap *envs)
{
	if (WIFSIGNALED(status))
		update_last_status(envs, 128 + WTERMSIG(status));
	if (WIFEXITED(status))
		update_last_status(envs, WEXITSTATUS(status));
}

void	dup_and_close(t_token *t)
{
	if (t->fd[0] != STDIN_FILENO)
	{
		dup2(t->fd[0], STDIN_FILENO);
		close(t->fd[0]);
	}
	if (t->fd[1] != STDOUT_FILENO)
	{
		dup2(t->fd[1], STDOUT_FILENO);
		close(t->fd[1]);
	}
}

void	close_not_used_fd(t_token *t)
{
	if (t->fd[0] != STDIN_FILENO)
		close(t->fd[0]);
	if (t->fd[1] != STDOUT_FILENO)
		close(t->fd[1]);
}

static void	update_last_status(t_hashmap *envs, int status)
{
	char	*str;

	str = ft_itoa(status);
	insert_pair(&envs, create_pair("?", str));
	free(str);
}
