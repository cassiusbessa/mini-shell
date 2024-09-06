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

static int	find_space_or_sep(char *input, int start)
{
	int	space;
	int	sep;

	space = 0;
	sep = 0;
	while (input[space + start] != ' ' && input[space + start])
		space++;
	if (!input[space + start])
		space = -1;
	sep = find_first_separator(input, start);
	if (space >= 0 && (space <= sep || sep < 0))
		return (space + start);
	if (sep >= 0 && (sep <= space || space < 0))
	{
		if (input[1 + start] && is_separator(input[0 + start]) && is_separator(input[1 + start]))
			sep += 2;
		return (sep + start);
	}
	return (ft_strlen(input));
}

static t_part	choose_index(char *input, t_part q, int token_index)
{
	t_part	p;

	p.start = 0;
	ft_printf("input:%s\n", input);
	if (token_index > q.start && token_index < q.end)
		return (p.end = find_space_or_sep(input, q.end), p);
	return (p.end = token_index, p);
	
}

char *get_next_token(char **input)
{
	int			token_index;
	char		*token;
	t_part	q;
	t_part	p;

	skip_spaces(input);
	q = quotes(*input);
	token_index = find_space_or_sep(*input, 0);
	if (token_index == 0)
		token_index++;
	p = choose_index(*input, q, token_index);
	ft_printf("start:%d, end:%d, choose:%d\n", q.start, q.end, p.end);
	token = ft_substr(*input, p.start, p.end - p.start);
	(*input) += p.end;
	return (token);
}

char *get_next_word(char **input)
{
	char	*word;
	if (!input || !(*input) || !(**input))
		return (NULL);
	skip_spaces(input);
	word = ft_substr(*input, 0, find_space_or_sep(*input, 0));
	skip_alphanum(input);
	skip_spaces(input);
	return (word);
}



