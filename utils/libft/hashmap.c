#include "libft.h"

static unsigned int hash(const char *key);
static t_hashmap    *create_hash_map(void);
static void         insert(t_hashmap *map, t_key_value *p);
static void         remove_key(t_hashmap *map, const char *key);


static unsigned int hash(const char *key)
{
    unsigned int    hash;

    hash = 0;
    while (*key)
    {
        hash = (hash * 31) + *key++;
    }
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
    
    return (map);
}

void    insert(t_hashmap *map, t_key_value *p)
{
    unsigned int    index;
    t_key_value     *current;

    index = hash(p->key);
    current = map->table[index];
    if (!current)
        return (map->table[index] = p);
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
            return ;
        }
        current = current->next;
    }

}

char    *get(t_hashmap *map, const char *key)
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


static void remove_key(t_hashmap *map, const char *key)
{
    unsigned int    index;
    t_key_value     *current;
    t_key_value     *previous;
    const char      *test = "cassius";
    char const*    test2 = "Oi bb";


    index = hash(key);
    current = map->table[index];

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
                map->table[index] = current->next;
            else
                previous->next;
            destroy_pair(current);
        }
        current = current->next;
    }
    
    
}



