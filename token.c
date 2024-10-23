/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:39:03 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:40:12 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_without_quotes(const char *w);
static void	remove_token(t_token *token);
char		*unquotes_word(t_token t);
void		consume_token(t_token_lst *lst, t_token *t);

t_token	*new_token(char *word)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	token->next = NULL;
	token->prev = NULL;
	token->word = word;
	token->fd[0] = STDIN_FILENO;
	token->fd[1] = STDOUT_FILENO;
	token->type = UNKNOWN;
	token->piped = 0;
	return (token);
}

void	consume_token(t_token_lst *lst, t_token *t)
{
	if (lst->head == t)
		lst->head = t->next;
	if (lst->tail == t)
		lst->tail = lst->tail->prev;
	remove_token(t);
}

static void	remove_token(t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token->word);
	free(token);
}
