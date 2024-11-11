/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:37:42 by cassius           #+#    #+#             */
/*   Updated: 2024/11/09 20:45:49 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_env(char *new_env);

int	unset_cmd(t_main *main)
{
	t_token	*temp;

	temp = main->token_lst->head->next;
	while (temp && temp->type == ARGUMMENT)
	{
		if (!is_valid_env(temp->word))
		{
			ft_printf("unset: %s: not a valid identifier\n", temp->word);
			update_last_status(main->envs, 0);
			return (1);
		}
		remove_key(&main->envs, temp->word);
		temp = temp->next;
	}
	update_last_status(main->envs, 0);
}

int	export_cmd(t_main *main)
{
	char	*k;
	char	*v;
	int		i;
	t_token	*temp;

	temp = main->token_lst->head->next;
	while (temp && temp->type == ARGUMMENT)
	{
		if (!is_valid_env(temp->word))
		{
			ft_printf("export: %s: not a valid identifier\n", temp->word);
			update_last_status(main->envs, 0);
			return (1);
		}
		i = find_equals(temp->word);
		k = ft_substr(temp->word, 0, i);
		v = ft_substr(temp->word, i + 1, ft_strlen(temp->word) - (i + 1));
		insert_pair(&main->envs, create_pair(k, v));
		free(k);
		free(v);
		temp = temp->next;
	}
	update_last_status(main->envs, 1);
	return (1);
}

static int	is_valid_env(char *new_env)
{
	int	i;

	if (!new_env || !new_env[0])
		return (0);
	if (!ft_isalpha(new_env[0]) && new_env[0] != '_')
		return (0);
	i = 1;
	while (new_env[i] && new_env[i] != '=')
	{
		if (!ft_isalnum(new_env[i]) && new_env[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
