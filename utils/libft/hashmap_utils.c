#include "libft.h"

void        print_hashmap(t_hashmap map);


void        print_hashmap(t_hashmap map)
{
    int i;
    t_key_value *current;
    int first;

    i = 0;
    current = NULL;
    first = 1;
    ft_printf("{\n");
    while (i < TABLE_SIZE)
    {
        current = map.table[i];
        while (current)
        {
            if (!first)
                ft_printf(",\n");
            ft_printf(" \"%s\": \"%s\"", current->key, current->value);
            current = current->next;
            first = 0;
        }
        i++;
    }
    ft_printf("\n}\n");
}
