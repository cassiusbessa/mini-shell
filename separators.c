/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:24:02 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/20 18:17:42 by caqueiro         ###   ########.fr       */
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
			{
				if (input[i + 1] && input[i + 1] == input[i])
					i++;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	find_first_separator(char *input)
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

int	is_separator(char c)
{
	int	i;

	i = 0;
	while (CH_SEP[i])
	{
		if (c == CH_SEP[i])
			return (1);
		i++;
	}
	return (0);
}