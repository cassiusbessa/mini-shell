/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:35:27 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:36:27 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_lst	*new_token_lst(void)
{
	return ((t_token_lst *)ft_calloc(1, sizeof(t_token_lst)));
}

void	add_token(t_token *token, t_main *main)
{
	if (!token && !main->token_lst)
		return ;
	if (!main->token_lst->head)
	{
		main->token_lst->head = token;
		main->token_lst->tail = token;
	}
	else
	{
		main->token_lst->tail->next = token;
		token->prev = main->token_lst->tail;
		main->token_lst->tail = token;
	}
}

void	destroy_token_lst(t_main *main)
{
	t_token	*current;
	t_token	*next;

	if (main->token_lst == NULL)
		return ;
	current = main->token_lst->head;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	free(main->token_lst);
	main->token_lst = NULL;
}

static int	is_separator_type(t_token *t)
{
	return (t->type == REDIR_IN || t->type == REDIR_OUT || t->type == HERE_DOC
		|| t->type == PIPE || t->type == APPEND);
}

int	sintax_validation(t_token_lst lst)
{
	t_token	*t;

	t = lst.head;
	while (t != NULL)
	{
		if ((is_separator_type(t)) && (t->type != PIPE) && (!t->next
				|| (t->next->type != DOCUMENT && t->next->type != HERE_DOC_EOF
					&& t->next->type != COMMAND)))
			return (0);
		if (t->type == PIPE)
		{
			if (t->prev == NULL)
				return (0);
			if (t->next == NULL || t->next->type == PIPE)
				return (0);
		}
		t = t->next;
	}
	return (1);
}
