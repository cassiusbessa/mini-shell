/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_separators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:24:02 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/25 20:49:51 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_separators(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		while(CH_SEP[j])
		{
			if (input[i] == CH_SEP[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}