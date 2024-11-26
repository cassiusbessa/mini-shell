/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:42:59 by cassius           #+#    #+#             */
/*   Updated: 2024/11/11 01:44:58 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(t_token *token)
{
	if (!ft_strcmp(token->word, "-n"))
		return (1);
	return (0);
}

int	echo_cmd(t_main *main)
{
	int		i;
	int		space;
	int		newline;
	int		only_flag;
	t_token	*tmp;

	only_flag = 0;
	tmp = main->token_lst->head->next;
	newline = 1;
	while (tmp && check_flag(tmp))
	{
		tmp = tmp->next;
		newline = 0;
	}
	space = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARGUMMENT)
			write(main->token_lst->head->fd[1], tmp->word, strlen(tmp->word));
		if (tmp && tmp->next != NULL && tmp->type != PIPE
			&& tmp->type == ARGUMMENT && tmp->next->type == ARGUMMENT)
			write(main->token_lst->head->fd[1], " ", 1);
		tmp = tmp->next;
	}
	if (newline)
		write(main->token_lst->head->fd[1], "\n", 1);
	update_last_status(main->envs, 0);
	return (1);
}

int	builtins(t_main *main)
{
	/*if (!ft_strcmp(main->token_lst->head->word, "exit"))
		return (exit_cmd(main->token_lst), 1);*/
	if (!ft_strcmp(main->token_lst->head->word, "env"))
		return (env_cmd(main), 1);
	else if (!ft_strcmp(main->token_lst->head->word, "pwd"))
		return (pwd_cmd(main), 1);
	else if (!ft_strcmp(main->token_lst->head->word, "echo"))
		return (echo_cmd(main), 1);
	else if (!strcmp(main->token_lst->head->word, "cd"))
		return (cd_cmd(main), 1);
	else if (!ft_strcmp(main->token_lst->head->word, "unset"))
		return (unset_cmd(main), 1);
	else if (!ft_strcmp(main->token_lst->head->word, "export"))
		return (export_cmd(main), 1);
	return (0);
}