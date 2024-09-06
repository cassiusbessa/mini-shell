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

int	find_first_separator(char *input, int start)
{
	int	i;
	int	j;

	i = 0;
	while (input[i + start])
	{
		j = 0;
		while(CH_SEP[j])
		{
			if (input[i + start] == CH_SEP[j])
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

t_part	quotes(char *input)
{
	t_part	quotes;
	int			i;
	int			d;
	int			s;

	quotes.start = -1;
	quotes.end = -1;
	i = 0;
	d = 0;
	s = 0;
	if (input[i] != 34 && input[i] != 39)
		return (quotes);
	quotes.start = i;
	if (input[i] == 34 && d == 0 && s == 0)
		d = 1;
	else if (input[i] == 39 && s == 0 && d == 0)
		s = 1;
	i++;
	while (input[i])
	{
		if (input[i] == 34 && d > 0 && s == 0)
		{
			if (!input[i + 1] || (input[i + 1] && (input[i + 1] == ' ' || is_separator(input[i + 1]))))
			{
				quotes.end = i;
				d = 0;
			}
			else if (input[i + 1] && input[i + 1] == 39)
			{
				quotes.end = -1;
				s = 1;
				d = 0;
				i++;
			}
		}
		else if (input[i] == 39 && s > 0 && d == 0)
		{
			if (!input[i + 1] || (input[i + 1] && (input[i + 1] == ' ' || is_separator(input[i + 1]))))
			{
				quotes.end = i;
				s = 0;
			}
			else if (input[i + 1] && input[i + 1] == 34)
			{
				quotes.end = -1;
				d = 1;
				s = 0;
				i++;
			}
		}
		if (quotes.start != -1 && quotes.end != -1)
			return (quotes);
		i++;
	}
	ft_printf("d:%d, s:%d\n", d, s);
	if (d == 0 && s == 0 && !input[i])
	{
		quotes.end = i;
	}
	return quotes;
}