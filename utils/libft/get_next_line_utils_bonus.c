/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:20:23 by caqueiro          #+#    #+#             */
/*   Updated: 2024/01/31 22:29:57 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, void *content)
{
	t_list	*new;
	t_list	*current;

	new = (t_list *)malloc(sizeof (t_list));
	if (!new)
		return ;
	new->content = content;
	new->next = NULL;
	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_list(t_list **lst)
{
	t_list	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		*lst = current->next;
		free(current->content);
		free(current);
		current = *lst;
	}
	*lst = NULL;
}

size_t	line_len(t_list *lst)
{
	t_list	*current;
	size_t	count;
	char	*content;

	if (!lst)
		return (0);
	current = lst;
	count = 0;
	while (current)
	{
		content = current->content;
		while (*content)
		{
			if (*content == '\n')
				return (count + 1);
			content++;
			count++;
		}
		current = current->next;
	}
	return (count);
}
