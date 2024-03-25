/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:29:49 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/25 19:23:30 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char **input)
{
	while (**input == ' ' && **input)
		(*input)++;
}

static void skip_alphanum(char **input)
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

char *get_next_word(char **input)
{
	char	*word;
	if (!input || !(*input) || !(**input))
		return (NULL);
	skip_spaces(input);
	word = ft_substr(*input, 0, find_space(*input));
	skip_alphanum(input);
	skip_spaces(input);
	return (word);
}