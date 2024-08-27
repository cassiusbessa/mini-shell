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

static void	skip_len(char **input, int len)
{
	while (**input && len > 0)
	{
		(*input)++;
		len--;
	}
}

static int	find_space_or_sep(char *input)
{
	int	space;
	int	sep;

	space = 0;
	sep = 0;
	while (input[space] != ' ' && input[space])
		space++;
	if (!input[space])
		space = -1;
	sep = find_first_separator(input);
	if (space >= 0 && (space <= sep || sep < 0))
		return (space);
	if (sep >= 0 && (sep <= space || space < 0))
		return (sep);
	return (ft_strlen(input));
}

char *get_next_token(char **input)
{
	int		token_index;
	char	*token;

	skip_spaces(input);
	token_index = find_space_or_sep(*input);
	if (token_index == 0)
		token_index++;
	token = ft_substr(*input, 0, token_index);
	(*input) += token_index;
	return (token);
}

char *get_next_word(char **input)
{
	char	*word;
	if (!input || !(*input) || !(**input))
		return (NULL);
	skip_spaces(input);
	word = ft_substr(*input, 0, find_space_or_sep(*input));
	skip_alphanum(input);
	skip_spaces(input);
	return (word);
}



