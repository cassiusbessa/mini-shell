/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:39:29 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:41:55 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist_command(t_token_lst *lst)
{
	t_token	*current;

	current = lst->head;
	while (current)
	{
		if (current->type == COMMAND)
			return (1);
		current = current->next;
	}
	return (0);
}

int	exist_pipe(t_main *main)
{
	t_token	*current;

	current = main->token_lst->head;
	while (current)
	{
		if (current->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

void	type_document_argumment(t_main *main)
{
	int		command;
	int		pipe;
	t_token	*current;

	command = 0;
	pipe = exist_pipe(main);
	current = main->token_lst->head;
	while (current)
	{
		if (current->type == UNKNOWN && command)
			current->type = ARGUMMENT;
		if (current->type == UNKNOWN && !command)
		{
			current->type = COMMAND;
			command = 1;
		}
		if (current->type == PIPE)
			command = 0;
		current = current->next;
	}
}

static void	set_token_type(t_token *current)
{
	if (!ft_strcmp(current->word, "|"))
		current->type = PIPE;
	else if (!ft_strcmp(current->word, ">"))
		current->type = REDIR_OUT;
	else if (!ft_strcmp(current->word, "<"))
		current->type = REDIR_IN;
	else if (!ft_strcmp(current->word, "<<"))
		current->type = HERE_DOC;
	else if (!ft_strcmp(current->word, ">>"))
		current->type = APPEND;
	else if (current->prev && !ft_strcmp(current->prev->word, "<<"))
		current->type = HERE_DOC_EOF;
	else if (current->prev && (!ft_strcmp(current->prev->word, ">")
			|| !ft_strcmp(current->prev->word, "<")
			|| !ft_strcmp(current->prev->word, ">>")))
		current->type = DOCUMENT;
}

void	type_tokens(t_main *main)
{
	t_token	*current;
	t_token	*next;

	current = main->token_lst->head;
	while (current)
	{
		next = current->next;
		set_token_type(current);
		current = next;
	}
	type_document_argumment(main);
}
