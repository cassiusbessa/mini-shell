/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:37:54 by caqueiro          #+#    #+#             */
/*   Updated: 2024/04/11 18:28:40 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*find_cmd_path(t_token *cmd, t_hashmap *envs)
{
	char				**env_path;
	char				*cmd_path;
	struct stat 		file_stat;
	int					i;

	i = 0;
	env_path = ft_split(get_value(envs, "PATH"), ':');
	while (env_path[i])
	{
		cmd_path = join_path(env_path[i], cmd->word);

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