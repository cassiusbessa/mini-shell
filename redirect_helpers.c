/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:38:44 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:38:45 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_out(t_token *curr, t_token *curr_cmd, int has_cmd);
static void	redir_in(t_token *curr, t_token *curr_cmd, int has_cmd);
static void	append(t_token *curr, t_token *curr_cmd, int has_cmd);
static void	here_doc(t_token *curr, t_token *curr_cmd, int has_cmd);

void	handle_redir_types(t_token *curr, t_token *curr_cmd)
{
	int	has_cmd;

	has_cmd = (curr_cmd != NULL);
	if (!curr || !curr->prev)
		return ;
	if (curr->prev->type == REDIR_OUT)
		redir_out(curr, curr_cmd, has_cmd);
	else if (curr->prev->type == REDIR_IN)
		redir_in(curr, curr_cmd, has_cmd);
	else if (curr->prev->type == APPEND)
		append(curr, curr_cmd, has_cmd);
	else if (curr->prev->type == HERE_DOC)
		here_doc(curr, curr_cmd, has_cmd);
}

static void	redir_out(t_token *curr, t_token *curr_cmd, int has_cmd)
{
	int	fd;

	fd = open(curr->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (has_cmd)
		curr_cmd->fd[1] = fd;
	else
		close(fd);
}

static void	redir_in(t_token *curr, t_token *curr_cmd, int has_cmd)
{
	int	fd;

	fd = open(curr->word, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		ft_printf("minishell: %s: No such file or directory\n", curr->word);
		return ;
	}
	if (has_cmd)
		curr_cmd->fd[0] = fd;
	else
		close(fd);
}

static void	append(t_token *curr, t_token *curr_cmd, int has_cmd)
{
	int	fd;

	fd = open(curr->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (has_cmd)
		curr_cmd->fd[1] = fd;
	else
		close(fd);
}

static void	here_doc(t_token *curr, t_token *curr_cmd, int has_cmd)
{
	int	fd;

	fd = here_doc_redirect(curr->word);
	if (has_cmd)
		curr_cmd->fd[0] = fd;
	else
		close(fd);
	curr_cmd->here_doc = 1;
}
