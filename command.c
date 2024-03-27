/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:48:15 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/27 19:53:30 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_command	*new_cmd(void)
{
	t_command	*cmd;

	cmd = (t_command *)ft_calloc(1, sizeof (t_command));
  cmd->args = NULL;
  cmd->flags = NULL;
  cmd->instruction = NULL;
  cmd->separator = NULL;
  cmd->next = NULL;
	return (cmd);
}

static t_list	*build_flags(char **input)
{
	t_list	*flags;

  if (!input || !*input)
	return (NULL);
	flags = new_lst();
	while (**input == '-' && **input)
		add_back(new_node(get_next_word(input)), &flags);
	return (flags);
}

static t_list	*build_args(char **input)
{
	t_list	*args;

  if (!input || !*input)
	return (NULL);
	args = new_lst();
	while (**input)
		add_back(new_node(get_next_word(input)), &args);
	return (args);
}

t_command	*build_command(char **input)
{
	t_command	*cmd;
	int				sep;
	char			*until_separator;
	char			*bkp;

	sep = find_separators(*input);
	until_separator = *input;
	bkp = NULL;
	if (sep >= 0)
	{
		until_separator = ft_substr(*input, 0, sep);
		*input += sep + 1;
		bkp	=	until_separator;
	}
	else
		*input += ft_strlen(*input);
	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	cmd->instruction = get_next_word(&until_separator);
	if (*until_separator == '-')
		cmd->flags = build_flags(&until_separator);
	cmd->args = build_args(&until_separator);
	cmd->separator = get_next_word(&until_separator);
	free(bkp);
	return (cmd);
}
