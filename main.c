/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/10 00:22:12 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
  t_main      main;
	char        *read;
  char        *str;

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
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main() {
//     int pipefd[2];
//     char buffer[256];
//     pid_t pid;

//     // Cria o pipe
//     if (pipe(pipefd) == -1) {
//         perror("Erro ao criar o pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Cria um novo processo filho
//     pid = fork();

//     if (pid == -1) {
//         perror("Erro ao criar o processo filho");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) { // Processo filho
// 	    // Fecha a extremidade de escrita do pipe
//         close(pipefd[1]);
//         // Lê a mensagem do pipe
//         read(pipefd[0], buffer, sizeof(buffer));
//         // Imprime a mensagem lida
//         printf("filho leu:%s\n", buffer);
//         // Fecha a extremidade de leitura do pipe
//         close(pipefd[0]);
//     } else { // Processo pai
// 		// Fecha a extremidade de leitura do pipe
//         close(pipefd[0]);
//         // Escreve a mensagem no pipe
//         write(pipefd[1], "Eu sou o pai\n", 13);
//         // Fecha a extremidade de escrita do pipe
//         close(pipefd[1]);
// 		wait(NULL);
//         // Encerra o processo pai
//         exit(EXIT_SUCCESS);
//     }

//     return 0;
// }