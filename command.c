/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:48:15 by caqueiro          #+#    #+#             */
/*   Updated: 2024/03/22 15:58:30 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*build_flags(char **input)
{
	t_list	*flags;

  if (!input || *input)
    return (NULL);
	flags = new_lst();
	while (**input == '-' && **input)
		add_back(new_node(get_next_word(input)), &flags);
	return (flags);
}

static t_list	*build_args(char **input)
{
	t_list	*args;

  if (!input || *input)
    return (NULL);
	args = new_lst();
	while (**input)
		add_back(new_node(get_next_word(input)), &args);
	return (args);
}

t_command	*build_command(char **input)
{
	t_command	*cmd;

	cmd = (t_command *)ft_calloc(1, sizeof (t_command));
  cmd->args = NULL;
  cmd->flags = NULL;
  cmd->instruction = NULL;
  cmd->separator = NULL;
  cmd->next = NULL;
	if (!cmd)
		return (NULL);
	cmd->instruction = get_next_word(input);
	if (**input == '-')
		cmd->flags = build_flags(input);
	cmd->args = build_args(input);
	cmd->separator = get_next_word(input);
	return (cmd);
}
