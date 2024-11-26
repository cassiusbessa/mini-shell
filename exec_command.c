/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 21:06:55 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_command(t_main *main);
static void	handle_main_process(t_token **t, t_main *main);
static void	handle_child_process(t_main *main);
static void	consume_to_next_cmd(t_token **t, t_main *main);

void	exec_all_commands(t_main *main)
{
	t_token	*t;
	t_token	*tmp;
	pid_t	pid;
	int		status;

	t = main->token_lst->head;
	pre_exec(main->token_lst);
	while (t)
	{
		if (t && t->type == COMMAND)
		{
			if (!builtins(main))
				handle_child_process(main);
			handle_main_process(&t, main);
		}
		else
			consume_to_next_cmd(&t, main);
	}
	while (wait(&status) > 0)
		update_last_status(main->envs, status);
	setup_sigaction_handler();
}

static void	handle_child_process(t_main *main)
{
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
