/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:04:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/07 20:56:51 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int here_doc_redirect(char *eof)
{
    char    *line;
    pid_t   pid;
    int     here_doc_fd[2];

    if (pipe(here_doc_fd) == -1)
        perror("pipe");
    while (1)
    {
        line = readline(">");
        if (!line)
            exit(EXIT_FAILURE);
        if (!ft_strcmp(line, eof))
        {
            free(line);
            break;
        }
        write(here_doc_fd[1], line, ft_strlen(line));
        write(here_doc_fd[1], "\n", 1);
        free(line);
    }
    close(here_doc_fd[1]);
    return(here_doc_fd[0]);
}

void static close_all_files(t_command *cmd)
{
    
}

void handle_output_redirect(t_command **cmd)
{
    int fd_in;
    int fd_out;
    t_command *current_cmd;

    fd_in = STDIN_FILENO;
    fd_out = STDOUT_FILENO;
    current_cmd = *cmd;

    while (current_cmd && check_separator(">>", *cmd) || check_separator(">", *cmd) || check_separator("<", *cmd) || check_separator("<<", *cmd))
    {
        if (check_separator(">>", current_cmd))
            fd_out = open(current_cmd->doc, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else if (check_separator(">", current_cmd))
        {
            fd_out = open(current_cmd->doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (current_cmd->fd[0] != STDIN_FILENO)
                close(current_cmd->fd[0]);
            if (current_cmd->fd[1] != STDOUT_FILENO)
                close(current_cmd->fd[1]);

        }
        else if (check_separator("<<", current_cmd))
            fd_in = here_doc_redirect(current_cmd->doc);
        else if (check_separator("<", current_cmd))
            fd_in = open(current_cmd->doc, O_RDONLY);
        else if (check_separator("|", current_cmd))
        if (fd_out < 0 || fd_in < 0)
            exit(EXIT_FAILURE);
        current_cmd->fd[0] = fd_in;
        current_cmd->fd[1] = fd_out;
        if (!current_cmd->next)
        {
            current_cmd->flags = copy_lst((*cmd)->flags);
            if (!current_cmd->instruction)
                current_cmd->instruction = ft_strdup((*cmd)->instruction);
            current_cmd->args = copy_lst((*cmd)->args);
            break ;
        }
        current_cmd = current_cmd->next;
    }
    (*cmd) = current_cmd;
}
