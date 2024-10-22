/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:46:17 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/21 22:51:40 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quote(const char *str, int *i);
static void	skip_spaces(const char *str, int *i);
static void	handle_special_operators(char *input, t_part *part);

char	*get_next_token(char *input)
{
	static char		*cmp;
	static t_part	part;
	char			*token_str;

	if (!input)
		return (NULL);
	skip_spaces(input, &part.start);
	part.end = part.start;
	while (*(input + part.end) && (!ft_strchr(" \t\n<>|", *(input + part.end))))
		if (!skip_quote(input, &part.end))
			part.end++;
	handle_special_operators(input, &part);
	token_str = ft_substr(input, part.start, (part.end - part.start));
	if (part.start == part.end)
	{
		free(token_str);
		token_str = NULL;
		ft_memset(&part, 0, sizeof(part));
	}
	part.start = part.end;
	return (token_str);
}

static int	skip_quote(const char *str, int *i)
{
	char	quote;

	if (!str || ((*(str + *i) != '\'') && (*(str + *i) != '"')))
		return (0);
	quote = *(str + *i);
	*i += 1;
	while (*(str + *i) && (*(str + *i) != quote))
		*i += 1;
	if (*(str + *i))
		*i += 1;
	return (1);
}

void	handle_special_operators(char *input, t_part *part)
{
	if (part->end == part->start && *(input + part->start))
	{
		if (ft_strchr("<>", *(input + part->end)) && *(input
				+ part->end) == *(input + part->end + 1))
			part->end++;
		part->end++;
	}
}

static void	skip_spaces(const char *str, int *i)
{
	if (!str)
		return ;
	while (*(str + *i) && ft_strchr(" \n\t\r\f\v", *(str + *i)))
		*i += 1;
}
