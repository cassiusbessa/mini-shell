/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/09 20:30:33 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_size(t_command *cmd)
{
	int	size;

	if (!cmd)
		return (0);
	size = 0;
	if (cmd->args)
		size += cmd->args->size;
	if (cmd->flags)
		size += cmd->flags->size;
	return (size);
}
char	**list_to_args(t_command *cmd)
{
	char		**args;
	int			size;
	int			i;
	t_node		*current;

	size = args_size(cmd);
	if (!cmd || !size)
		return (NULL);
	args = (char **)ft_calloc(size + 2, sizeof (char *));
	i = 0;
	args[i++] = cmd->instruction;
	if (cmd->flags)
	{
		current = cmd->flags->head;
		while (current)
		{
			args[i++] = current->value;
			current = current->next;
		}
	}
	if (cmd->args)
	{
		current = cmd->args->head;
		while (current)
		{
			args[i++] = current->value;
			current = current->next;
		}
	}
	args[i] = NULL;
	return (args);
}

void exec_command(t_command *cmd) {
    char **args;

    if (!cmd)
        return;
    args = list_to_args(cmd);
    set_cmd_path(cmd);
    execve(cmd->path, args, NULL);
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
		{
            if (current->next && ft_strncmp("|", current->separator, ft_strlen(current->separator)) == 0)  
			{
                // Se houver um próximo comando, redirecione a saída padrão para o pipe de escrita
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]); // Feche o descritor de arquivo de leitura no processo filho
            } else 
			{
                // Se não houver próximo comando, não é necessário criar um novo pipe
                close(fd[0]); // Feche o descritor de arquivo de leitura no processo filho
                close(fd[1]); // Feche o descritor de arquivo de gravação no processo filho
            }

            // Conecta a entrada padrão ao pipe de leitura do comando anterior
            dup2(prev_fd, STDIN_FILENO);

            // Executa o comando
            exec_command(current);
        } else 
		{
            // Pai espera pelo filho
            waitpid(pid, NULL, 0);
            close(prev_fd); // Fecha o descritor de arquivo usado no loop anterior
            prev_fd = fd[0]; // Salva o descritor de arquivo de leitura para o próximo loop
            close(fd[1]); // Feche o descritor de arquivo de gravação no processo pai
        }
        current = current->next;
    }
    // close(prev_fd); // Fecha o descritor de arquivo usado no último loop
}