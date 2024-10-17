#include "minishell.h"

void				pipe_all_cmds(t_token_lst *lst);
void				redir_next_cmd(t_token_lst *lst);
static int	here_doc_redirect(const char *eof);
static void	write_to_here_doc(int write_fd, const char *eof);
static void	handle_redir_types(t_token *curr, t_token *curr_cmd);

void	pipe_all_cmds(t_token_lst *lst)
{
	t_token	*cur;
	t_token	*cur_cmd;
	t_token	*nxt_cmd;
	int			fd[2];

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
			if (curr_cmd && (curr_cmd->fd[0] != STDIN_FILENO || curr_cmd->fd[1] != STDOUT_FILENO) && !curr_cmd->here_doc)
			{
				close_not_used_fd(curr_cmd);
				curr_cmd->piped = 0;
			}
			handle_redir_types(curr, curr_cmd);
		}
		curr = curr->next;
	}
}

void	redir_next_cmd(t_token_lst *lst)
{
	t_token	*curr;
	t_token	*nxt_cmd;
	t_token	*curr_cmd;

	curr = lst->head;
	curr_cmd = NULL;
	nxt_cmd = NULL;
	while (curr && !nxt_cmd)
	{
		if (curr->type == COMMAND && !curr_cmd)
			curr_cmd = curr;
		if (curr_cmd && curr->type == COMMAND && curr_cmd != curr)
			nxt_cmd = curr;
		if (curr && (curr->type == DOCUMENT || curr->type == HERE_DOC_EOF))
		{
			if (curr_cmd && curr_cmd->piped)
			{
				close_not_used_fd(curr_cmd);
				curr_cmd->piped = 0;
			}
			handle_redir_types(curr, curr_cmd);
		}
		curr = curr->next;
	}
}

static void	handle_redir_types(t_token *curr, t_token *curr_cmd)
{
	int	has_cmd;
	int	fd;

	has_cmd = 0;
	if (!curr)
		return ;
	if (curr_cmd)
		has_cmd = 1;
	fd = 0;
	if (curr->prev->type == REDIR_OUT)
	{
		fd = open(curr->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (has_cmd)
			curr_cmd->fd[1] = fd;
		else
			close(fd);
	}
	else if (curr->prev->type == REDIR_IN)
	{
		fd = open(curr->word, O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			ft_printf("minishell: %s: No such file or directory\n");
			return ;
		}
		if (has_cmd)
			curr_cmd->fd[0] = fd;
		else
			close(fd);
	}
	else if (curr->prev->type == APPEND)
	{
		fd = open(curr->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (has_cmd)
			curr_cmd->fd[1] = fd;
		else
			close(fd);
	}
	else if (curr->prev->type == HERE_DOC)
	{
		fd = here_doc_redirect(curr->word);
		if (has_cmd)
			curr_cmd->fd[0] = fd;
		else
			close(fd);
		curr_cmd->here_doc = 1;
	}
}


static int	here_doc_redirect(const char *eof)
{
	int		here_doc_fd[2];
	char	*line;
	int		pid;
	int		status;

	pipe(here_doc_fd);
	pid = fork();
	if (pid == 0)
	{
		close(here_doc_fd[0]);
		write_to_here_doc(here_doc_fd[1], eof);
		close(here_doc_fd[1]);
		exit(0);
	}
	else
	{
		close(here_doc_fd[1]);
		waitpid(pid, &status, 0);
		return (here_doc_fd[0]);
	}
}

static void	write_to_here_doc(int write_fd, const char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}


