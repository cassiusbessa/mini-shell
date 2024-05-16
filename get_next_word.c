/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:29:49 by caqueiro          #+#    #+#             */
/*   Updated: 2024/05/16 17:40:34 by gamoraes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char **input)
{
	while (**input == ' ' && **input)
		(*input)++;
}

static void	skip_alphanum(char **input)
{
	while (**input != ' ' && **input)
		(*input)++;
}

static int	find_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] != ' ' && input[i])
		i++;
	return (i);
}

char	*parse_word(char **input)
{
	char	*start;
	char	*end;
	char	quote;

	skip_spaces(input);
	start = *input;
	quote = 0;
	if (**input == '"' || **input == '\'')
	{
		quote = **input;
		start = ++(*input);
		while (**input && **input != quote)
			(*input)++;
		end = *input;
		if (**input == quote)
			(*input)++;
	}
	else
	{
		while (**input && !isspace(**input))
			(*input)++;
		end = *input;
	}
	return (ft_strndup(start, end - start));
}

char	*get_next_word(char **input)
{
	if (!input || !(*input) || !(**input))
		return (NULL);
	return (parse_word(input));
}
