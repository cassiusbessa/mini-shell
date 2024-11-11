/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:44:39 by cassius           #+#    #+#             */
/*   Updated: 2024/11/09 20:46:33 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_status(int new_status)
{
	static int	status;

	if (new_status > -1)
		status = new_status;
	return (status);
}

void	err(char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
}

void	error_env(char *cmd)
{
	err("env: '");
	err(cmd);
	err("': No such file or directory\n");
}

int	env_cmd(t_main	*main)
{
	t_token		*tmp;
	int			index;

	tmp = main->token_lst->head;
	index = 0;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->word, "env"))
			tmp = tmp->next;
		else
		{
			error_env(tmp->word);
			update_last_status(main->envs, 127);
			return (0);
		}
	}
	print_hashmap(*main->envs);
	update_last_status(main->envs, 0);
	return (1);
}
