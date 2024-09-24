/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/03 20:24:59 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char        *read;
  t_token_lst *token_lst;
  char        *str;
  t_hashmap   *envs;

  envs = build_envs(envp);
  destroy_hashmap(envs);
  token_lst = new_token_lst();
  read = readline("minishell% ");
  while (read)
  {
    add_history(read);
    str = get_next_token2(read);
    while (str != NULL)
    {
      add_token(new_token(str), &token_lst); 
      str = get_next_token2(read);
    }
    type_specials_token(token_lst);
    ft_printf("valido:%d\n", sintax_validation(*token_lst));
    print_token_lst(token_lst);
    rl_on_new_line();
    destroy_token_lst(&token_lst);
    free(read);
    read = readline("minishell% ");
    token_lst = new_token_lst();
  }
  destroy_token_lst(&token_lst);
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