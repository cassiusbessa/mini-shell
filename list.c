/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:18:32 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/22 15:59:54 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(char *value)
{
	t_node	*nd;

	nd = ft_calloc(1, sizeof (t_node));
	nd->value = value;
	nd->next = NULL;
}

t_list	*new_lst(void)
{
	return ((t_list *)ft_calloc(1, sizeof (t_list)));
}

void	add_back(t_node *n, t_list **lst)
{
	if (*lst == NULL)
		return ;
	if (!(*lst)->head)
	{
		(*lst)->head = n;
		(*lst)->tail = n;
	}
	else
	{
		(*lst)->tail->next = n;
		(*lst)->tail = n;
	}
}

void	destroy_list(t_list *lst)
{
	t_node	*current;
	t_node	*next;

	current = lst->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
  free(lst);
}
