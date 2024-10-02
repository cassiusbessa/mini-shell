#include "minishell.h"

void expand_env(t_hashmap *envs, char *key, t_part p, char *w)
{
    char    *value;
    char    *expanded;
    int     i;
    int     j;

    value = get_value(envs, key);
    expanded = (char *)ft_calloc(ft_strlen(w) - (p.end - p.start) + ft_strlen(value), sizeof(char));
    j = 0;
    i = 0;
    while (i < p.start - 1)
    {
        expanded[i] = w[i];
        i++;
    }
    while (value[j])
        expanded[i++] = value[j++];
    while (w[p.end])
        expanded[i++] = w[p.end++];
    expanded[i] = '\0';
    ft_printf("valor expandido: %s\n", expanded);
}