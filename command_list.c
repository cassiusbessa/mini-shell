/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:46:14 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/22 15:58:54 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*new_cmd_lst(void)
{
	return ((t_cmd_lst *)ft_calloc(1, sizeof (t_cmd_lst)));
}

void	add_cmd(t_command *cmd, t_cmd_lst **lst)
{
	if (!*lst || !lst)
		return ;
	if (!(*lst)->head)
	{
		(*lst)->head = cmd;
		(*lst)->tail = cmd;
	}
	else
	{
		(*lst)->tail->next = cmd;
		(*lst)->tail = cmd;
	}
}
