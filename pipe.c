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

    current = *cmd;
    while (current)
    {
        if (current->next && check_separator("|", current))
        {
            // Cria o pipe
            if (pipe(current->fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
			dup2(current->fd[1], STDOUT_FILENO);
			close(current->fd[0]);
			close(current->fd[1]);
            // Configura os descritores de arquivo para os comandos
            current->next->fd[0] = current->fd[0]; // O próximo comando lê do pipe
            current->next->fd[1] = STDOUT_FILENO; // Garantindo que o próximo comando tenha o stdout padrão, se não for sobrescrito
        }
        current = current->next;
    }
}

// void	handle_pipe(t_command *cmd, int fd[2])
// {
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	close(fd[1]);
// }
//kkk = 5
//ls > kkk (fd[0] = 12, fd[13]) (fd[0] = 12; fd[1] = 5) | wc -l (fd[0] = 0; fd[1] = 1)
