/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/09 20:55:45 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void exec_command(t_token_lst *l, t_hashmap *envs);
static  void handle_main_process(t_token **t, t_token_lst *lst);

void exec_all_commands(t_token_lst *lst, t_hashmap *envs)
{
  t_token *t;
  t_token *tmp;
  pid_t pid;

  t = lst->head;
	pipe_all_cmds(lst);
  while (t)
  {
    redir_next_cmd(lst);
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
  while(wait(NULL) > 0);
}

static void exec_command(t_token_lst *l, t_hashmap *envs)
{
  char **args;
  char *path;
	t_token *t;

  if (l->head->type != COMMAND)
    return ;
  args = build_args(*l);
  path = find_cmd_path(l->head, envs); 
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
	t = l->head;
	while (t)
	{
		close_not_used_fd(t);
		t = t->next;
	}
  execve(path, args, to_envp(*envs));
}

static void handle_main_process(t_token **t, t_token_lst *lst)
{
  t_token *tmp;

  close_not_used_fd(*t);
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