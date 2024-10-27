/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:37:14 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:38:37 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_to_here_doc(int write_fd, const char *eof);

int	here_doc_redirect(const char *eof)
{
	int		here_doc_fd[2];
	char	*line;
	int		pid;
	int		status;

	pipe(here_doc_fd);
	pid = fork();
	if (pid == 0)
	{
		close(here_doc_fd[0]);
		write_to_here_doc(here_doc_fd[1], eof);
		close(here_doc_fd[1]);
		exit(0);
	}
	else
	{
		close(here_doc_fd[1]);
		waitpid(pid, &status, 0);
		return (here_doc_fd[0]);
	}
}

static void	write_to_here_doc(int write_fd, const char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		write(write_fd, line, strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}
