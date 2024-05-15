/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:55:15 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/14 17:17:26 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_command *cmd, int fd[2])
{
	if (cmd->next && ft_strncmp("|", cmd->separator,
			ft_strlen(cmd->separator)) == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
}
