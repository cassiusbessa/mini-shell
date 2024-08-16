/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:55:15 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/07 23:14:04 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_pipe(t_command **cmd)
{
    t_command *current;
    int temp_fd[2];

    current = *cmd;
    while (current)
    {
        if (current->next && check_separator("|", current))
        {
            // Cria o pipe
            if (pipe(temp_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            // Configura os descritores de arquivo para os comandos
            // futuramente vai dar bug!
            current->fd[1] = temp_fd[1];
            current->next->fd[0] = temp_fd[0]; // O próximo comando lê do pipe
            //current->next->fd[1] = STDOUT_FILENO; // Garantindo que o próximo comando tenha o stdout padrão, se não for sobrescrito

        }
        current = current->next;
    }
}

// [Saída = 3] (3/4) [Entrada = 4/ Saída 5] (5/6) [Entrada = 6] []


// void	handle_pipe(t_command *cmd, int fd[2])
// {
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);
// }
//kkk = 5
//ls > kkk (fd[0] = 12, fd[13]) (fd[0] = 12; fd[1] = 5) | wc -l (fd[0] = 0; fd[1] = 1)
