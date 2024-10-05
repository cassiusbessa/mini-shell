/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/07 22:47:38 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_command(t_token_lst *l, t_hashmap *envs);
static char **build_args(t_token_lst l);
static void handle_main_process(t_token **t, t_token_lst *lst);
static void pipe_next_cmd(t_token_lst *lst);

void exec_all_commands(t_token_lst *lst, t_hashmap *envs)
{
  t_token *t;
  t_token *tmp;
  pid_t pid;

  t = lst->head;
  while (t)
  {
    pipe_next_cmd(lst);
    if (t->type == COMMAND)
    {
      pid = fork();
      if (pid == 0)
      {
        exec_command(lst, envs);
        exit(0);
      }
      else
        handle_main_process(&t, lst);
    }
    else
      t = t->next;
  }
  t = lst->head;
  while (t)
  {
    if (t->fd[0] != STDIN_FILENO)
      close(t->fd[0]);
    if (t->fd[1] != STDOUT_FILENO)
      close(t->fd[1]);
    t = t->next;
  }
}

static void exec_command(t_token_lst *l, t_hashmap *envs)
{
  char **args;
  char *path;
  int   i;

  args = build_args(*l);
  path = find_cmd_path(l->head, envs);
  i = 0;
  while (args[i])
    i++;  
  if (!path)
    exit(EXIT_FAILURE);
  if (l->head->fd[0] != STDIN_FILENO)
  {
    dup2(l->head->fd[0], STDIN_FILENO);
    close(l->head->fd[0]);
  }
  if (l->head->fd[1] != STDOUT_FILENO)
  {
    dup2(l->head->fd[1], STDOUT_FILENO);
    close(l->head->fd[1]);   
  }
  execve(path, args, to_envp(*envs));
}

static void pipe_next_cmd(t_token_lst *lst)
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
  }
}

static void handle_main_process(t_token **t, t_token_lst *lst)
{
  t_token *tmp;

  wait(NULL);
  if ((*t)->fd[0] != STDIN_FILENO)
    close((*t)->fd[0]);
  if ((*t)->fd[1] != STDOUT_FILENO)
    close((*t)->fd[1]);
  tmp = (*t)->next;
  consume_token(lst, *t);
  *t = tmp;
  while (*t && (*t)->type != COMMAND)
  {
      tmp = (*t)->next;
      consume_token(lst, *t);
      *t = tmp;
  }
}

static char  **build_args(t_token_lst l)
{
  t_token *tmp;
  int     i;
  char    **args;

  i = 0;
  tmp = l.head;
  while (tmp && tmp->type != PIPE )
  {
    if (tmp->type == COMMAND || tmp->type == ARGUMMENT)
      i++;
    tmp = tmp->next;
  }
  args = malloc(sizeof(char *) * (i + 1));
  i = 0;
  tmp = l.head;
  while (tmp && tmp->type != PIPE)
  {
    if (tmp->type == COMMAND || tmp->type == ARGUMMENT)
      args[i++] = tmp->word;
    tmp = tmp->next;
  }
  args[i] = NULL;
  return (args);
}



