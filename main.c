/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 21:56:13 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(char *read, t_main *main);

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	char	*read;

	setup_sigaction_handler();
	main.envs = build_envs(envp);
	//start_pwd(&main);
	main.token_lst = new_token_lst();
	read = readline("minishell% ");
	shell_loop(read, &main);
	destroy_token_lst(&main);
	destroy_hashmap(main.envs);
	rl_clear_history();
	return (0);
}

static void	shell_loop(char *read, t_main *main)
{
	char	*str;

	while (read)
	{
		add_history(read);
		str = get_next_token(read);
		while (str != NULL)
		{
			add_token(new_token(str), main);
			str = get_next_token(read);
		}
		type_tokens(main);
		expand_all_envs(main);
		exec_all_commands(main);
		rl_on_new_line();
		destroy_token_lst(main);
		free(read);
		read = readline("minishell% ");
		(*main).token_lst = new_token_lst();
	}
}
