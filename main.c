/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/16 18:17:45 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char        *read;
  t_token_lst *token_lst;
  char        *str;
  t_hashmap   *envs;

	setup_sigaction_handler();
  envs = build_envs(envp);
  token_lst = new_token_lst();
  read = readline("minishell% ");
  while (read)
  {
    add_history(read);
    str = get_next_token(read);
    while (str != NULL)
    {
      add_token(new_token(str), &token_lst); 
      str = get_next_token(read);
    }
    type_tokens(token_lst);
    expand_all_envs(envs, token_lst);
    exec_all_commands(token_lst, envs);
    rl_on_new_line();
    destroy_token_lst(&token_lst);
    free(read);
    read = readline("minishell% ");
    token_lst = new_token_lst();
  }
  destroy_token_lst(&token_lst);
  destroy_hashmap(envs);
  rl_clear_history();
	return (0);
}