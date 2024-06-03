/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:18:32 by caqueiro          #+#    #+#             */
/*   Updated: 2024/06/03 20:20:25 by caqueiro         ###   ########.fr       */
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
	t_list	*lst;

	lst = (t_list *)ft_calloc(1, sizeof (t_list));
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst);
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
	(*lst)->size++;
}

void	destroy_list(t_list *lst)
{
	t_node	*current;
	t_node	*next;

	if (!lst)
		return ;
	current = lst->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
  free(lst);
  lst = NULL;
}

t_list	*copy_lst(t_list *lst)
{
	t_list	*n_lst;
	t_node	*n_node;
	t_node	*current;

    if (!lst)
        return NULL;
	n_lst = new_lst();
    if (!new_lst)
        return NULL;
    current = lst->head;
    while (current)
    {
        n_node = new_node(ft_strdup(current->value));
        if (!n_node)
        {
			destroy_list(n_lst);
			return NULL;
        }
		add_back(n_node, &n_lst);
		current = current->next;
    }
    return n_lst;
}
