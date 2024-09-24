#include "libft.h"

static unsigned int hash(const char *key);
t_hashmap    *create_hash_map(void);
void         insert_pair(t_hashmap **map, t_key_value *p);
void         remove_key(t_hashmap **map, const char *key);
void         destroy_hashmap(t_hashmap *map);
char        *get_value(t_hashmap *map, const char *key);


static unsigned int hash(const char *key)
{
    unsigned int    hash;

    hash = 0;
    while (*key)
        hash = (hash * 31) + *key++;
    return (hash % TABLE_SIZE);
}

t_hashmap  *create_hash_map(void)
{
    t_hashmap   *map;
    int         i;

    map = ft_calloc(sizeof (t_hashmap), 1);
    map->table = ft_calloc(sizeof (t_key_value *), TABLE_SIZE);
    i = 0;
    while (i < TABLE_SIZE)
        map->table[i++] = NULL;
    map->size = 0;
    return (map);
}

void    insert_pair(t_hashmap **map, t_key_value *p)
{
    unsigned int    index;
    t_key_value     *current;

    index = hash(p->key);
    current = (*map)->table[index];
    if (!current)
    {
        (*map)->table[index] = p;
        (*map)->size++;
        return ;
    }
    while (current)
    {
        if (ft_strcmp(current->key, p->key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(p->value);
            return ;
        }
        if (current->next == NULL)
        {
            current->next = p;
            (*map)->size++;
            return ;
        }
        current = current->next;
    }
}

char    *get_value(t_hashmap *map, const char *key)
{
    unsigned int    index;
    t_key_value     *current;

    index = hash(key);
    current = map->table[index];
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}


void    remove_key(t_hashmap **map, const char *key)
{
    unsigned int    index;
    t_key_value     *current;
    t_key_value     *previous;

    index = hash(key);
    previous = NULL;
    current = (*map)->table[index];
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
                (*map)->table[index] = current->next;
            else
                previous->next = current->next;
            destroy_pair(current);
            (*map)->size--;
            return ;
        }
        previous = current;
        current = current->next;
    }
}

void    destroy_hashmap(t_hashmap *map)
{
    int             i;
    t_key_value     *current;
    t_key_value     *temp;

    i = 0;
    temp = NULL;
    current = NULL;
    while (i < TABLE_SIZE)
    {
        current = map->table[i];
        while (current)
        {
            temp = current;
            current = current->next;
            destroy_pair(temp);
        }
        i++;
    }
    free(map->table);
    free(map);
} 