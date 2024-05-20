/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:46:14 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/20 18:37:32 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*new_cmd_lst(void)
{
	return ((t_cmd_lst *)ft_calloc(1, sizeof (t_cmd_lst)));
}

void	add_cmd(t_command *cmd, t_cmd_lst **lst)
{
	if (!cmd || !*lst || !lst)
		return ;
	if (!(*lst)->head)
	{
		(*lst)->head = cmd;
		(*lst)->tail = cmd;
	}
	else
	{
		(*lst)->tail->next = cmd;
    cmd->prev = (*lst)->tail;
		(*lst)->tail = cmd;
	}
}

void  destroy_cmd_lst(t_cmd_lst *lst)
{
  t_command *current;
  t_command *next;

  current = lst->head;
  while (current)
  {
    next = current->next;
    destroy_list(current->args);
    destroy_list(current->flags);
    free(current->instruction);
    free(current->separator);
    free(current->doc);
    free(current->path);
    free(current);
    current = next;
  }
  free(lst);
}
