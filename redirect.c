#include "minishell.h"

void pipe_next_cmd(t_token_lst *lst);
void redir_next_cmd(t_token_lst *lst);
static int here_doc_redirect(const char *eof);
static void write_to_here_doc(int write_fd, const char *eof);
void  close_not_used_fd(t_token *t);

void pipe_next_cmd(t_token_lst *lst)
{
  t_token *current;
  t_token *nxt_command;
  t_token *curr_command;
  int fd[2];

  current = lst->head;
  if (!current)
    return ;
  nxt_command = NULL;
  curr_command = NULL;
  while (current && !nxt_command)
  {
    if (current->type == COMMAND && !curr_command)
      curr_command = current;
    if (curr_command && current->type == COMMAND && curr_command != current)
      nxt_command = current;
    current = current->next;
  }
  if (curr_command && nxt_command && nxt_command->prev && nxt_command->prev->type == PIPE)
  {
    pipe(fd);
    curr_command->fd[1] = fd[1];
    nxt_command->fd[0] = fd[0];
    curr_command->piped = 1;
  }
}

static int find_pipe(t_token *t)
{
  t_token *cur;

  cur = t;
  while (cur)
  {
    if (cur->type == PIPE)
      return (1);
    cur = cur->next;
  }
  return (0);
}

void  pipe_all_cmds(t_token_lst *lst)
{
  t_token *cur;
  t_token *cur_cmd;
  t_token *nxt_cmd;
  int fd[2];

  cur = lst->head;
  cur_cmd = NULL;
  nxt_cmd = NULL;
  while (cur)
  {
    if (cur->type == COMMAND && !cur_cmd)
    {
      cur_cmd = cur;
      ft_printf("Found first command: %s\n", cur_cmd->word);
    }
    if (cur_cmd && cur->type == COMMAND && cur_cmd != cur)
    {
      nxt_cmd = cur;
      ft_printf("Found next command: %s\n", nxt_cmd->word);
    }
    if (cur_cmd && nxt_cmd && nxt_cmd->prev && nxt_cmd->prev->type == PIPE)
    {
      ft_printf("Creating pipe between %s and %s\n", cur_cmd->word, nxt_cmd->word);
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

void redir_next_cmd(t_token_lst *lst)
{
  t_token *curr;
  t_token *nxt_cmd;
  t_token *curr_cmd;

  curr = lst->head;
  if (!curr)
    return ;
  curr_cmd = NULL;
  nxt_cmd = NULL;
  while (curr && !nxt_cmd)
  {
    if (curr->type == COMMAND && !curr_cmd)
      curr_cmd = curr;
    if (curr_cmd && curr->type == COMMAND && curr_cmd != curr)
      nxt_cmd = curr;
    if (curr->type == DOCUMENT || curr->type == HERE_DOC_EOF)
    {
      if (curr_cmd->piped)
      {
        close_not_used_fd(curr_cmd);
        curr_cmd->piped = 0;
      }
      if (curr->prev->type == REDIR_OUT)
        curr_cmd->fd[1] = open(curr->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      else if (curr->prev->type == REDIR_IN)
        curr_cmd->fd[0] = open(curr->word, O_RDONLY);
      else if (curr->prev->type == APPEND)
        curr_cmd->fd[1] = open(curr->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
      else if (curr->prev->type == HERE_DOC)
        curr_cmd->fd[0] = here_doc_redirect(curr->word);
    }
    curr = curr->next;
  }
}

static int here_doc_redirect(const char *eof)
{
  int here_doc_fd[2];
  char *line;
  int pid;
  int status;

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
    return here_doc_fd[0];
  }
}

static void write_to_here_doc(int write_fd, const char *eof)
{
  char *line;

  while (1)
  {
    line = readline("> ");
    if (!line)
      break;
    if (!ft_strcmp(line, eof))
    {
      free(line);
      break;
    }
    write(write_fd, line, strlen(line));
    write(write_fd, "\n", 1);
    free(line);
  }
  close(write_fd);
}

void close_not_used_fd(t_token *t)
{
  if (t->fd[0] != STDIN_FILENO)
    close(t->fd[0]);
  if (t->fd[1] != STDOUT_FILENO)
    close(t->fd[1]);
}