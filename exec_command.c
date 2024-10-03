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
static char  **build_args(t_token_lst l);

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


void exec_all_commands(t_token_lst *lst, t_hashmap *envs)
{
  t_token *t;
  t_token *tmp;
  pid_t pid;

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
  execve(path, args, to_envp(*envs));
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

