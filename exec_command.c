/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/20 20:41:44 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_separator(char *sep, t_command *cmd)
{
	if (!cmd || !cmd->separator)
		return (0);
	return (ft_strncmp(sep, cmd->separator,
			ft_strlen(cmd->separator)) == 0);
}

static void exec_command(t_command *cmd) {
    char **args;

    if (!cmd)
        return;
    args = list_to_args(cmd);
    set_cmd_path(cmd);
	execve(cmd->path, args, NULL);
}

static void handle_child_process(t_command *cmd, int fd[2], int prev_fd) {
    int here_doc_fd[2];

    // Primeiro tratamos o here-doc, se houver
    if (check_separator("<<", cmd)) {
        if (pipe(here_doc_fd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        here_doc_redirect(cmd, cmd->doc, here_doc_fd);
        cmd = cmd->next; // Avançamos para o próximo comando
    }

    // Em seguida tratamos os redirecionamentos de saída
    if (check_separator("|", cmd)) {
        handle_pipe(cmd, fd);
    } else if (check_separator(">", cmd)) {
        handle_output_redirect(cmd, cmd->doc);
    } else if (check_separator(">>", cmd)) {
        handle_output_append(cmd, cmd->doc);
    } else if (check_separator("<", cmd)) {
        handle_input_redirect(cmd, cmd->doc);
    } else {
        close(fd[0]);
        close(fd[1]);
    }

    dup2(prev_fd, STDIN_FILENO);
    exec_command(cmd);
}


static void	handle_main_process(int fd[2], int *prev_fd)
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	*prev_fd = fd[0];
	close(fd[1]);
}

void exec_all_commands(t_cmd_lst *lst) {
    t_command *current;
    pid_t pid;
    int fd[2];
    int prev_fd;

    current = lst->head;
	prev_fd = STDIN_FILENO;
    while (current) 
	{
        if (pipe(fd) == -1) 
            return;
        pid = fork();
        if (pid == 0) 
			handle_child_process(current, fd, prev_fd);
		else 
			handle_main_process(fd, &prev_fd);
        current = current->next;
    }
	while (wait(NULL) > 0);
}
