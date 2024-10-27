/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 21:31:33 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	char	*read;
	char	*str;

	setup_sigaction_handler();
	main.envs = build_envs(envp);
	main.token_lst = new_token_lst();
	read = readline("minishell% ");
	while (read)
	{
		add_history(read);
		str = get_next_token(read);
		while (str != NULL)
		{
			add_token(new_token(str), &main);
			str = get_next_token(read);
		}
		type_tokens(&main);
		expand_all_envs(&main);
		exec_all_commands(&main);
		rl_on_new_line();
		destroy_token_lst(&main);
		free(read);
		read = readline("minishell% ");
		main.token_lst = new_token_lst();
	}
	destroy_token_lst(&main);
	destroy_hashmap(main.envs);
	rl_clear_history();
	return (0);
}
