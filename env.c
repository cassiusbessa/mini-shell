/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:27:02 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/09 20:47:36 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hashmap	*build_envs(char **envp);
int			find_equals(char *s);
static char	*build_line(t_key_value *kv);
char		**to_envp(t_hashmap *envs);

t_hashmap	*build_envs(char **envp)
{
	int			i;
	t_hashmap	*envs;
	char		*k;
	char		*v;

	envs = create_hash_map();
	i = 0;
	k = NULL;
	v = NULL;
	while (*envp)
	{
		i = find_equals(*envp);
		k = ft_substr(*envp, 0, i);
		v = ft_substr(*envp, i + 1, ft_strlen(*envp) - (i + 1));
		insert_pair(&envs, create_pair(k, v));
		free(k);
		free(v);
		envp++;
	}
	insert_pair(&envs, create_pair("?", "0"));
	return (envs);
}

int	find_equals(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static char	*build_line(t_key_value *kv)
{
	char	*env;

	env = NULL;
	if (kv->value)
	{
		env = ft_calloc(ft_strlen(kv->key) + ft_strlen(kv->value) + 2,
				sizeof(char));
		ft_strlcpy(env, kv->key, ft_strlen(kv->key) + 1);
		ft_strlcat(env, "=", ft_strlen(env) + 2);
		ft_strlcat(env, kv->value, ft_strlen(env) + ft_strlen(kv->value) + 1);
	}
	else
	{
		env = ft_calloc(ft_strlen(kv->key) + 2, sizeof(char));
		ft_strlcpy(env, kv->key, ft_strlen(kv->key) + 1);
		ft_strlcat(env, "=", ft_strlen(env) + 2);
	}
	return (env);
}

char	**to_envp(t_hashmap *envs)
{
	char		**envp;
	t_part		i;
	t_key_value	*current;

	current = NULL;
	envp = (char **)ft_calloc(envs->size + 1, sizeof(char *));
	i.start = 0;
	i.end = 0;
	while (i.start < TABLE_SIZE)
	{
		current = envs->table[i.start];
		while (current)
		{
			envp[i.end++] = build_line(current);
			current = current->next;
		}
		i.start++;
	}
	envp[i.end] = NULL;
	return (envp);
}
