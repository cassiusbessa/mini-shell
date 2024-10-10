#include "minishell.h"

static int size_without_quotes(const char *w);
int validate_quotes(char *w);
char    *unquotes_word(t_token t);
void		unquotes_all_words(t_token_lst *lst);

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
        if ((t.word[i] == 34 || t.word[i] == 39) && type == 0)
            type = t.word[i];
        else if (t.word[i] == type)
            type = 0;
        else
            w[j++] = t.word[i];
        i++;
    }
    return (w);
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

int validate_quotes(char *w)
{
    int i;
    int type;

    i = 0;
    type = 0;
    while (w[i])
    {
        if ((w[i] == 34 || w[i] == 39) && type == 0)
            type = w[i];
        else if (w[i] == type)
            type = 0;
        i++;
    }
    return (type);
}

void    unquotes_all_words(t_token_lst *lst)
{
	t_token *t;
	char		*tmp;

	t = lst->head;
	while (t)
	{
		tmp = unquotes_word(*t);
		free(t->word);
		t->word = tmp;
		t = t->next;
	}
}