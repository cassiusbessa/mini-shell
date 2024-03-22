/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:18:32 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/21 21:04:26 by caqueiro         ###   ########.fr       */
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