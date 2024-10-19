/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:37:54 by caqueiro          #+#    #+#             */
/*   Updated: 2024/10/10 00:03:28 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*absolute_path(t_main *main);
static char	*join_path(char const *s1, char const *s2);
static char	*find_cmd_path(t_main *main);

char	*absolute_path(t_main *main)
{
	if (access(main->token_lst->head->word, F_OK) == 0)
		return (ft_strdup(main->token_lst->head->word));
	return (find_cmd_path(main));//alterar função head e main
}

static char	*join_path(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = malloc(sizeof (char) * (i + j) + 2);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	join[j++] = '/';
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

static char	*find_cmd_path(t_main *main)
{
	char				**env_path;
	char				*cmd_path;
	struct stat 		file_stat;
	int					i;

	i = 0;
	env_path = ft_split(get_value(main->envs, "PATH"), ':');
	while (env_path[i])
	{
		cmd_path = join_path(env_path[i], main->token_lst->head->word);

		if (stat(cmd_path, &file_stat) >= 0)
		{
			destroy_2d((void **)env_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	destroy_2d((void **)env_path);
	return (NULL);
}
