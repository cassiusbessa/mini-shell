/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:39:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/07 20:25:19 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_double_pointer(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	ft_printf("args:\n");
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_all_commands(t_cmd_lst *lst)
{
  t_command *current;
  t_command *next;

  current = lst->head;
  while (current)
  {
    next = current->next;
	print_command(current);
    current = next;
  }
}

void	print_command(t_command *cmd)
{
	if (!cmd)
	{
		ft_printf("null cmd\n");
		return ;
	}
	ft_printf("instruction:%s\n", cmd->instruction);
    ft_printf("flags:\n");
    print_list(cmd->flags);
    ft_printf("args:\n");
    print_list(cmd->args);
    ft_printf("separator:%s\n", cmd->separator);
	ft_printf("doc:%s\n", cmd->doc);
    ft_printf("path:%s\n", cmd->path);
	ft_printf("fd[0]:%d, fd[1]:%d\n", cmd->fd[0], cmd->fd[1]);

}

void	print_list(t_list *lst)
{
	t_node *current;

	if (!lst)
		return ;
	current = lst->head;
	while (current != NULL)
	{
		ft_printf("%s\n", current->value);
		current = current->next;
	}
}
