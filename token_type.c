#include "minishell.h"

void    type_specials_token(t_token_lst *lst)
{
    t_token *current;
    t_token *next;
    ft_printf("entrei\n");

    current = lst->head;
    while(current)
    {
        next = current->next;
        if (!ft_strcmp(current->word, ">"))
            current->type = REDIR_IN;
        else if (ft_strcmp(current->word, ">>"))
            current->type = APPEND;
        else if (ft_strcmp(current->word, "<"))
            current->type = REDIR_IN;
        else if (ft_strcmp(current->word, "<<"))
            current->type = HERE_DOC;
        else if (ft_strcmp(current->word, "|"))
            current->type = PIPE;
        current = next;
    }
}