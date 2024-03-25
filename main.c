/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:42:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/25 20:37:47 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char        *read;
  char        *bkp;
  t_cmd_lst   *cmd_lst;

  cmd_lst = new_cmd_lst();
	read = readline("minishell% ");
  bkp = read;
	while (read)
	{
		add_history(bkp);
    while (*read)
      add_cmd(build_command(&read), &cmd_lst);
		rl_on_new_line();
    free(bkp);
		read = readline("minishell% ");
    bkp = read;
	}
  //ft_printf("%s\n", cmd_lst->tail->args);
  //destroy_cmd_lst(cmd_lst);
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