#include "minishell.h"


// 1 - percorrer string procurando $ sem aspas simples aberta;
// 2 - puxar valor da env e pegar o seu tamanho e soma com o len total do input;
// 3 - mallocar de novo com o tamanho total
// 4 - copiar mudando o valor

static int handle_quotes(char c, int quotes)
{
    if (c == '\'' && quotes == 0)
        return c;
    if (c == quotes)
        return 0;
    return quotes;
}

static t_part find_variable_brackets(char *w, int *i)
{
    t_part p;

    (*i)++;
    p = (t_part){.start = *i, .end = 0};
    while (w[*i] && w[*i] != '}')
        (*i)++;
    p.end = *i;
    return p;
}

static t_part find_variable_name(char *w, int *i)
{
    t_part p;

    p = (t_part){.start = *i, .end = 0};
    while (w[*i] && (isalnum((int)w[*i]) || w[*i] == '_'))
        (*i)++;
    p.end = *i;
    return p;
}

t_part find_env(char *w)
{
    int i;
    int quotes;
    t_part p;

    quotes = 0;
    p = (t_part){0};
    i = 0;
    while (w[i])
    {
        quotes = handle_quotes(w[i], quotes);
        if (w[i] == '$' && !quotes)
        {
            i++;
            if (ft_isdigit(w[i]))
                return (p.start = i, p.end = -1, p);
            if (w[i] == '{')
                return find_variable_brackets(w, &i);
            else if (ft_isalpha(w[i]) || w[i] == '_')
                return find_variable_name(w, &i);
        }
        i++;
    }
    return p;
}

char    *get_env_key(char *w, t_part p)
{
    return (ft_substr(w, p.start, p.end - p.start));
}