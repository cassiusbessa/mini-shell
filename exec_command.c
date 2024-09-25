/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/07 22:47:38 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_separator(char *sep, t_command *cmd)
// {
// 	if (!cmd || !cmd->separator)
// 		return (0);
// 	return (!ft_strcmp(sep, cmd->separator));
// }

// static void exec_command(t_command *cmd) {
//     char **args;

//     if (!cmd || !cmd->instruction)
//         return;
//     args = list_to_args(cmd);
//     set_cmd_path(cmd);
//     if (!cmd->path && !cmd->doc)
//         exit(EXIT_FAILURE);
// 	execve(cmd->path, args, NULL);
// }

// static void handle_fds(t_command **cmd)
// {
//         handle_output_redirect(cmd);
// }

// static void	handle_main_process(t_command *cmd)
// {
//     if (cmd->fd[0] != STDIN_FILENO)
//         close(cmd->fd[0]);
//     if (cmd->fd[0] != STDOUT_FILENO)
//         close(cmd->fd[1]);
// }

// void exec_all_commands(t_cmd_lst *lst)
// {
//     t_command *current;
//     pid_t pid;
//     t_command *temp;

//     current = lst->head;
//     handle_pipe(&current);
//     handle_fds(&current);

//     while (current)
//     {
//         if (current->instruction)
//         {
//             pid = fork();
//             if (pid == 0) 
//             {  // Processo filho
//                 if (current->fd[0] != STDIN_FILENO)
//                     dup2(current->fd[0], STDIN_FILENO);
//                 if (current->fd[1] != STDOUT_FILENO)
//                     dup2(current->fd[1], STDOUT_FILENO);
//                 temp = lst->head;
//                 while (temp)
//                 {
//                     if (temp->fd[0] != STDIN_FILENO)
//                         close(temp->fd[0]);
//                     if (temp->fd[1] != STDOUT_FILENO)
//                     {
//                         close(temp->fd[1]);
//                     }
//                     temp = temp->next;
//                 }
//                 exec_command(current);
//             } 
//             else
//             { // Pai
//                 if (current->fd[0] != STDIN_FILENO)
//                     close(current->fd[0]);
//                 if (current->fd[1] != STDOUT_FILENO)
//                     close(current->fd[1]);
//             }
//         }
//         current = current->next;
//     }
//     while (wait(NULL) > 0);
// }

