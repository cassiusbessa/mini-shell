/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 21:12:19 by caqueiro          #+#    #+#             */
/*   Updated: 2024/04/01 22:15:02 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_args(t_list *lst)
{
	char		**args;
	int			i;
	t_node	*current;

	if (!lst || !lst->head)
		return (NULL);
	current = lst->head;
	i = 0;
	args = ft_calloc(lst->size + 1, sizeof (char *));
	while (current && i < lst->size)
	{
		args[i] = current->value;
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	print_double_pointer(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		i++;
	}
}