/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/16 12:05:52 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_command(t_main *main);
static void handle_main_process(t_token **t, t_main *main);
static void	update_last_status(t_hashmap  *env, int status);
static void consume_to_next_cmd(t_token **t, t_main *main);
static void close_all_tokens_fd(t_token_lst *lst);

void exec_all_commands(t_main *main)
{
  t_token *t;
  t_token *tmp;
  pid_t 	pid;
	int 		status;

  t = main->token_lst->head;
	unquotes_all_words(main->token_lst);
	pipe_all_cmds(main->token_lst);
	redir_all_cmds(main->token_lst);
  while (t)
  {
    if (t && t->type == COMMAND)
    {
      printf("entrei no if\n");
      pid = fork();
      if (pid == 0)
      {
        exec_command(main);
        exit(0);
      }
      else
        handle_main_process(&t, main);
    }
    else
    {
      printf("entrei no else\n");
      consume_to_next_cmd(&t, main);
    }
  }
  while (wait(&status) > 0)
  {
		if (WIFSIGNALED(status))
			update_last_status(main->envs, 128 + WTERMSIG(status));
    if (WIFEXITED(status))
			update_last_status(main->envs, WEXITSTATUS(status));
  }
	setup_sigaction_handler();
}

static void exec_command(t_main *main)
{
  char **args;
  char *path;
	t_token *t;

  if (main->token_lst->head->type != COMMAND)
    return ;
  args = build_args(main);
  path = absolute_path(main);
  if (!path)
	{
		ft_printf("%s: command not found\n", main->token_lst->head->word);
		exit(127);
	}
  if (main->token_lst->head->fd[0] != STDIN_FILENO)
  {
    dup2(main->token_lst->head->fd[0], STDIN_FILENO);
    close(main->token_lst->head->fd[0]);
  }
  if (main->token_lst->head->fd[1] != STDOUT_FILENO)
  {
    dup2(main->token_lst->head->fd[1], STDOUT_FILENO);
    close(main->token_lst->head->fd[1]);   
  }
	t = main->token_lst->head;
	while (t)
	{
		close_not_used_fd(t);
		t = t->next;
	}
  execve(path, args, to_envp(main->envs));
}

static void handle_main_process(t_token **t, t_main *main)
{
  close_not_used_fd(*t);
  consume_to_next_cmd(t, main);
}

static void consume_to_next_cmd(t_token **t, t_main *main)
{
  t_token *tmp;

  tmp = (*t)->next;
  consume_token(main->token_lst, *t);
  *t = tmp;
  while (*t && (*t)->type != COMMAND)
  {
    tmp = (*t)->next;
    consume_token(main->token_lst, *t);
    *t = tmp;
  }
}

void close_not_used_fd(t_token *t)
{
	if (t->fd[0] != STDIN_FILENO)
		close(t->fd[0]);
	if (t->fd[1] != STDOUT_FILENO)
		close(t->fd[1]);
}

static void close_all_tokens_fd(t_token_lst *lst)
{
	t_token *t;

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

static void	update_last_status(t_hashmap  *env, int status)
{
	char	*str;

	str = ft_itoa(status);
	insert_pair(&env, create_pair("?", str));
	free(str);
}