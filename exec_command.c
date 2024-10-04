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
static void pipe_token_lst(t_token_lst *lst);
static void handle_main_process(t_token **t, t_token_lst *lst);

void exec_all_commands(t_token_lst *lst, t_hashmap *envs)
{
  t_token *t;
  t_token *tmp;
  pid_t pid;

  pipe_token_lst(lst);
  t = lst->head;
  while (t)
  {
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

static void pipe_token_lst(t_token_lst *lst)
{
    t_token *command = NULL;
    t_token *current = lst->head;
    t_token *prev_command = NULL;
    t_token *tmp = NULL;
    int pipe_fd[2];  // Variável temporária para armazenar o pipe atual

    while (current)
    {
        if (current->type == COMMAND)
        {
            command = current;

            // Se houver um comando anterior, conecte os pipes
            if (prev_command && prev_command->type == COMMAND)
            {
                prev_command->fd[1] = pipe_fd[1]; // Escreve no pipe
                command->fd[0] = pipe_fd[0];      // Lê do pipe
            }
            prev_command = command;
        }

        if (current->type == PIPE)
        {
            // Criar um novo pipe
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            // Consumir o token de pipe
            tmp = current->next;
            consume_token(lst, current);
            current = tmp;
            continue;
        }
        current = current->next;
    }
}

static void handle_main_process(t_token **t, t_token_lst *lst)
{
  t_token *tmp;

  wait(NULL);
  tmp = (*t)->next;
  consume_token(lst, *t);
  *t = tmp;
  while (*t && (*t)->type != COMMAND)
  {
      tmp = (*t)->next;
      consume_token(lst, *t);
      *t = tmp;
  }
  print_token_lst(lst);
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



