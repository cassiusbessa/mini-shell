/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/28 19:25:24 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_main *main);
static void	handle_main_process(t_token **t, t_main *main);
static void	handle_child_process(t_main *main, pid_t *last);
static void	consume_to_next_cmd(t_token **t, t_main *main);

void	exec_all_commands(t_main *main)
{
	t_token	*t;
	pid_t	pid;
	int		status;
	pid_t	last;

	t = main->token_lst->head;
	pre_exec(main->token_lst);
	while (t)
	{
		if (t && t->type == COMMAND)
		{
			if (!builtins(main))
				handle_child_process(main, &last);
			handle_main_process(&t, main);
		}
		else
			consume_to_next_cmd(&t, main);
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last)
			update_status(status, main->envs);
		pid = waitpid(-1, &status, 0);
	}
	setup_sigaction_handler();
}

static void	handle_child_process(t_main *main, pid_t *last)
{
	t_token	*t;

	t = main->token_lst->head->next;
	while (t && t->type != COMMAND)
		t = t->next;
	if (!t)
	{
		*last = fork();
		if (*last == 0)
		{
			setup_sigaction_child();
			exec_command(main);
			exit(0);
		}
		else
			return ;
	}
	if (fork() == 0)
	{
		setup_sigaction_child();
		exec_command(main);
		exit(0);
	}
}

static void	exec_command(t_main *main)
{
	char	**args;
	char	*path;
	t_token	*t;

	if (main->token_lst->head->type != COMMAND)
		return ;
	args = build_args(main);
	path = absolute_path(main);
	if (!path)
	{
		ft_printf("%s: command not found\n", main->token_lst->head->word);
		exit(127);
	}
	dup_and_close(main->token_lst->head);
	t = main->token_lst->head;
	while (t)
	{
		close_not_used_fd(t);
		t = t->next;
	}
	execve(path, args, to_envp(main->envs));
}

static void	handle_main_process(t_token **t, t_main *main)
{
	close_not_used_fd(*t);
	consume_to_next_cmd(t, main);
}

static void	consume_to_next_cmd(t_token **t, t_main *main)
{
	t_token	*tmp;

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
