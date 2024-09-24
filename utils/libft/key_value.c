#include "libft.h"

t_key_value *create_pair(const char *key, const char *value);
void        destroy_pair(t_key_value *p);
void        print_pair(t_key_value p);

t_key_value *create_pair(const char *key, const char *value)
{
    t_key_value *pair;

    pair = (t_key_value *)ft_calloc(sizeof (t_key_value), 1);
    pair->key = ft_strdup(key);
    pair->value = ft_strdup(value);
    pair->next = NULL;
    return (pair);
}

void    destroy_pair(t_key_value *p)
{
    if (p == NULL)
        return ;
    free(p->key);
    free(p->value);
    free(p);
    p = NULL;
}