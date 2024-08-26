#include "minishell.h"

t_token *new_token(char *word)
{
    t_token *token;

    token = (t_token *)ft_calloc(1, sizeof (t_token));

    token->next = NULL;
    token->prev = NULL;
    token->word = word;
    token->fd[0] = STDIN_FILENO;
    token->fd[1] = STDOUT_FILENO;
    token->type = UNKNOWN;
    return (token);
}