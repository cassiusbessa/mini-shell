/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 20:39:51 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 22:52:52 by caqueiro         ###   ########.fr       */
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

void	print_token(t_token *token)
{
	ft_printf("word:%s\n", token->word);
	ft_printf("type:%d\n", token->type);
	ft_printf("fd[0]:%d, fd[1]:%d\n", token->fd[0], token->fd[1]);
}

void	print_token_lst(t_token_lst *lst)
{
	t_token	*current;
	t_token	*next;

	current = lst->head;
	while (current)
	{
		next = current->next;
		print_token(current);
		current = next;
	}
}
