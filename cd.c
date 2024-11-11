/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:59:32 by cassius           #+#    #+#             */
/*   Updated: 2024/11/11 01:42:40 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	home_cd(t_main *main, t_token *tmp);
static int	oldpwd_cd(t_main *main, t_token *tmp);
static int	cd(t_main *main, t_token *tmp);

int	cd_cmd(t_main *main)
{
	t_token	*tmp;

	tmp = main->token_lst->head->next;
	if (home_cd(main, tmp))
		return (1);
	if (tmp && tmp->next && tmp->next->type == ARGUMMENT)
	{
		ft_printf("cd: too many arguments\n");
		update_last_status(main->envs, 1);
		return (1);
	}
	if (oldpwd_cd(main, tmp))
		return (1);
	return (cd(main, tmp));
}

static int	home_cd(t_main *main, t_token *tmp)
{
	char		*path;
	char		*current_path;

	if (!tmp || ft_strcmp(tmp->word, "~") == 0)
	{
		path = get_value(main->envs, "HOME");
		if (path == NULL)
		{
			ft_printf("cd error:%s\n", "HOME is not set");
			update_last_status(main->envs, 1);
		}
		current_path = getcwd(NULL, 0);
		chdir(path);
		insert_pair(&main->envs, create_pair("OLDPWD", current_path));
		free(current_path);
		update_last_status(main->envs, 0);
		return (1);
	}
	return (0);
}

static int	oldpwd_cd(t_main *main, t_token *tmp)
{
	char		*path;
	char		*current_path;

	if (ft_strcmp(tmp->word, "-") == 0)
	{
		path = get_value(main->envs, "OLDPWD");
		if (path == NULL)
		{
			ft_printf("cd error:%s\n", "OLDPWD is not set");
			update_last_status(main->envs, 1);
		}
		current_path = getcwd(NULL, 0);
		chdir(path);
		insert_pair(&main->envs, create_pair("OLDPWD", current_path));
		free(current_path);
		update_last_status(main->envs, 0);
		return (1);
	}
	return (0);
}

static int	cd(t_main *main, t_token *tmp)
{
	char		*path;
	char		*current_path;

	if (chdir(tmp->word) == -1)
		ft_printf("cd: %s: No such file or directory\n", tmp->word);
	update_last_status(main->envs, 0);
	current_path = getcwd(NULL, 0);
	insert_pair(&main->envs, create_pair("OLDPWD", current_path));
	free(current_path);
	return (1);
}
