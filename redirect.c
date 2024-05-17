/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:04:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/16 20:58:39 by caqueiro         ###   ########.fr       */
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

void	here_doc_redirec(t_command *cmd, char *eof)
{
	
}
