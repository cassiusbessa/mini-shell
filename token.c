#include "minishell.h"

static int     size_without_quotes(const char *w);
char    *unquotes_word(t_token t);

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

static int size_without_quotes(const char *w)
{
    int size;
    int i;
    int type;

    size = 0;
    i = 0;
    type = 0;
    while (w[i])
    {
        if ((w[i] == 34 || w[i] == 39) && type == 0)
            type = w[i];
        else if (w[i] == type)
            type = 0;
        else
            size++;
        i++;
    }
    return (size);
}


char    *unquotes_word(t_token t)
{
    char    *w;
    int     i;
    int     type;
    int     j;

    type = 0;
    w = (char *)ft_calloc(size_without_quotes(t.word) + 1, sizeof(char));
    j = 0;
    i = 0;
    type = 0;
    while (t.word[i])
    {
        if (t.word[i] == 34 || t.word[i] == 39 && type == 0)
            type = t.word[i];
        else if (t.word[i] == type)
            type = 0;
        else
            w[j++] = t.word[i];
        i++;
    }
    return (w);
}