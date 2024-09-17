#include "minishell.h"

t_token_lst *new_token_lst(void)
{
    return (t_token_lst *)ft_calloc(1, sizeof(t_token_lst));
}

void    add_token(t_token *token, t_token_lst **lst)
{
  if (!token || !*lst || !lst)
    return ;
  if (!(*lst)->head)
  {
    (*lst)->head = token;
    (*lst)->tail = token;
  }
  else
	{
		(*lst)->tail->next = token;
    token->prev = (*lst)->tail;
		(*lst)->tail = token;
	}
}

void  destroy_token_lst(t_token_lst **lst)
{
  t_token *current;
  t_token *next;

  if (*lst == NULL)
    return ;

  current = (*lst)->head;
  while (current)
  {
    next = current->next;
    free(current->word);
    free(current);
    current = next;
  }
  free((*lst));
  (*lst) = NULL;
}