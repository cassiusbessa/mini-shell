/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/10 02:05:33 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_command(t_main *main);
static void handle_main_process(t_token **t, t_main *main);
static void	update_last_status(t_main *main, int status);
static void consume_to_next_cmd(t_token **t, t_main *main);

void exec_all_commands(t_main *main)
{
  t_token *t;
  t_token *tmp;
  pid_t 	pid;
	int 		status;

  t = main->token_lst->head;
	unquotes_all_words(main);
	pipe_all_cmds(main);
  while (t)
  {
    redir_next_cmd(main);
    if (t && t->type == COMMAND)
    {
      if (!builtins(main))
      {
        printf("entrei no if\n");
        pid = fork();
        if (pid == 0)
        {
          exec_command(main);
          exit(0);
        }
      }
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
    if (WIFEXITED(status))
			update_last_status(main, WEXITSTATUS(status));
  }
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

static void	update_last_status(t_main *main, int status)
{
	char	*str;

	str = ft_itoa(status);
	insert_pair(&main->envs, create_pair("?", str));
	free(str);
}