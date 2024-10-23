/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:31:44 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:31:45 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hashmap			*create_hash_map(void);
void				insert_pair(t_hashmap **map, t_key_value *p);
void				remove_key(t_hashmap **map, const char *key);
char				*get_value(t_hashmap *map, const char *key);
static void			conflict_insert(t_hashmap **map, t_key_value *p,
						t_key_value *c);

t_hashmap	*create_hash_map(void)
{
	t_hashmap	*map;
	int			i;

	map = ft_calloc(sizeof(t_hashmap), 1);
	map->table = ft_calloc(sizeof(t_key_value *), TABLE_SIZE);
	i = 0;
	while (i < TABLE_SIZE)
		map->table[i++] = NULL;
	map->size = 0;
	return (map);
}

void	insert_pair(t_hashmap **map, t_key_value *p)
{
	unsigned int	index;
	t_key_value		*current;

	index = hash(p->key);
	current = (*map)->table[index];
	if (!current)
	{
		(*map)->table[index] = p;
		(*map)->size++;
	}
	else
		conflict_insert(map, p, current);
}

static void	conflict_insert(t_hashmap **map, t_key_value *p, t_key_value *c)
{
	while (c)
	{
		if (ft_strcmp(c->key, p->key) == 0)
		{
			free(c->value);
			c->value = ft_strdup(p->value);
			destroy_pair(p);
			return ;
		}
		if (c->next == NULL)
		{
			c->next = p;
			(*map)->size++;
			return ;
		}
		c = c->next;
	}
}

char	*get_value(t_hashmap *map, const char *key)
{
	unsigned int	index;
	t_key_value		*current;

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

void	remove_key(t_hashmap **map, const char *key)
{
	unsigned int	index;
	t_key_value		*current;
	t_key_value		*previous;

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
