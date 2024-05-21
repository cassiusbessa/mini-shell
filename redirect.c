/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:04:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/20 21:05:56 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_output_append(t_command *cmd, char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_output_redirect(t_command *cmd, char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_input_redirect(t_command *cmd, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
    	exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void here_doc_redirect(t_command *cmd, char *eof, int here_doc_fd[2]) {
    char *line;

    while (1) {
        line = readline(">");
        if (!line) {
            perror("readline");
            exit(EXIT_FAILURE);
        }
        if (!ft_strcmp(line, eof)) {
            free(line);
            break;
        }
        write(here_doc_fd[1], line, ft_strlen(line));
        write(here_doc_fd[1], "\n", 1);
        free(line);
    }
    close(here_doc_fd[1]);
    dup2(here_doc_fd[0], STDIN_FILENO);
    close(here_doc_fd[0]);
}


