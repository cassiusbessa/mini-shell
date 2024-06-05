/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:04:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/05 19:08:39 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// O PRIMEIRO COMANDO TEM QUE TER O FD IN E OUT DOS ÚLTIMOS
void handle_output_redirect(t_command **cmd)
{
    int fd_out;
    int fd_in;
    t_command *current_cmd;

    fd_out = STDOUT_FILENO;
    fd_in = STDIN_FILENO;
    current_cmd = *cmd;

    while (current_cmd)
    {
        if (check_separator(">>", current_cmd))
            fd_out = open(current_cmd->doc, O_CREAT | O_WRONLY | O_APPEND, 0644);
        else if (check_separator(">", current_cmd))
            fd_out = open(current_cmd->doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        else if (check_separator("<", current_cmd))
            fd_in = open(current_cmd->doc, O_RDONLY);
        if (fd_out < 0 || fd_in < 0)
            exit(EXIT_FAILURE);
        current_cmd->fd[0] = fd_in;
        current_cmd->fd[1] = fd_out;
        if (!current_cmd->next)
        {
            current_cmd->flags = copy_lst((*cmd)->flags);
            current_cmd->instruction = ft_strdup((*cmd)->instruction);
            current_cmd->args = copy_lst((*cmd)->args);
            break ;
        }
        current_cmd = current_cmd->next;
    }
    (*cmd) = current_cmd;
}

// void    handle_output_redirect(t_command **cmd)
// {
// 	int fd_out;

//     fd_out = STDOUT_FILENO;
//     if (check_separator(">>", (*cmd)))
// 	    fd_out = open((*cmd)->doc, O_CREAT | O_WRONLY | O_APPEND, 0644);
//     else
//         fd_out = open((*cmd)->doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     while ((*cmd) && (check_separator(">>", (*cmd)->next) || check_separator(">", (*cmd)->next) || check_separator("<", (*cmd)->next)))
//     {
//         close (fd_out);
//         if (check_separator(">>", (*cmd)))
// 	        fd_out = open((*cmd)->next->doc, O_CREAT | O_WRONLY | O_APPEND, 0644);
//         else
//             fd_out = open((*cmd)->next->doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//         if (fd_out == -1)
//             exit(EXIT_FAILURE);
//         (*cmd)->next->instruction = ft_strdup((*cmd)->instruction);
//         (*cmd)->next->args = copy_lst((*cmd)->args);
//         (*cmd) = (*cmd)->next;
//     }
// 	(*cmd)->fd[1] = fd_out;
// }

void handle_input_redirect(t_command **cmd)
{
    int fd;

    fd = open((*cmd)->doc, O_RDONLY);
    ft_printf("O fd foi alterado para:%d\n", fd);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    while ((*cmd) && check_separator("<", (*cmd)->next))
    {
        fd = open((*cmd)->next->doc, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        (*cmd)->next->instruction = ft_strdup((*cmd)->instruction);
        (*cmd)->next->args = copy_lst((*cmd)->args);
        (*cmd) = (*cmd)->next;
    }
    (*cmd)->fd[0] = fd;
}

int here_doc_redirect(t_command *cmd, char *eof)
{
    char *line;
    pid_t pid;
    int here_doc_fd[2];


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
    // dup2(here_doc_fd[0], STDIN_FILENO);
    return(here_doc_fd[0]);
}