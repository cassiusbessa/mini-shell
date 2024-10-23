/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:33:46 by cassius           #+#    #+#             */
/*   Updated: 2024/10/22 20:33:48 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				print_hashmap(t_hashmap map);
unsigned int		hash(const char *key);

void	print_hashmap(t_hashmap map)
{
	int			i;
	t_key_value	*current;
	int			first;

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

void	destroy_hashmap(t_hashmap *map)
{
	int			i;
	t_key_value	*current;
	t_key_value	*temp;

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

unsigned int	hash(const char *key)
{
	unsigned int	hash;

	hash = 0;
	while (*key)
		hash = (hash * 31) + *key++;
	return (hash % TABLE_SIZE);
}
