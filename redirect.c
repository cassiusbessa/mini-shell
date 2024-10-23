/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:55:16 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/22 20:34:54 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		pipe_all_cmds(t_token_lst *lst);
void		redir_all_cmds(t_token_lst *lst);

void	pipe_all_cmds(t_token_lst *lst)
{
	t_token	*cur;
	t_token	*cur_cmd;
	t_token	*nxt_cmd;
	int		fd[2];

	cur = lst->head;
	cur_cmd = NULL;
	nxt_cmd = NULL;
	while (cur)
	{
		if (cur->type == COMMAND && !cur_cmd)
			cur_cmd = cur;
		if (cur_cmd && cur->type == COMMAND && cur_cmd != cur)
			nxt_cmd = cur;
		if (cur_cmd && nxt_cmd && nxt_cmd->prev && nxt_cmd->prev->type == PIPE)
		{
			pipe(fd);
			cur_cmd->fd[1] = fd[1];
			nxt_cmd->fd[0] = fd[0];
			cur->piped = 1;
			cur_cmd = nxt_cmd;
			nxt_cmd = NULL;
		}
		cur = cur->next;
	}
}

void	redir_all_cmds(t_token_lst *lst)
{
	t_token	*curr;
	t_token	*nxt_cmd;
	t_token	*curr_cmd;

	curr = lst->head;
	curr_cmd = NULL;
	nxt_cmd = NULL;
	while (curr)
	{
		if (curr && curr->type == COMMAND && !curr_cmd)
			curr_cmd = curr;
		if (curr && curr_cmd && curr->type == COMMAND && curr_cmd != curr)
			nxt_cmd = curr;
		if (curr && (curr->type == DOCUMENT || curr->type == HERE_DOC_EOF))
		{
			if (curr_cmd && (curr_cmd->fd[0] != STDIN_FILENO
					|| curr_cmd->fd[1] != STDOUT_FILENO) && !curr_cmd->here_doc)
			{
				close_not_used_fd(curr_cmd);
				curr_cmd->piped = 0;
			}
			handle_redir_types(curr, curr_cmd);
		}
		curr = curr->next;
	}
}
