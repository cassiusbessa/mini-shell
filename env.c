#include "minishell.h"

t_hashmap   *build_envs(char **envp);
static char *build_line(t_key_value *kv);

t_hashmap   *build_envs(char **envp)
{
    char        **env_split;
    t_hashmap   *envs;

    envs = create_hash_map();
    while (*envp)
    {
        env_split = ft_split(*envp, '=');
        insert_pair(&envs, create_pair(env_split[0], env_split[1]));
        free(env_split[0]);
        free(env_split[1]);
        free(env_split);
        envp++;
    }
    return (envs);
}

static char *build_line(t_key_value *kv)
{
    char    *env;

    env = NULL;

    if (kv->value)
    {
        env = ft_calloc(ft_strlen(kv->key) + ft_strlen(kv->value) + 2, sizeof(char));

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

char    **to_envp(t_hashmap map)
{
    char    **envp;
    t_part     i;
    t_key_value *current;

    current = NULL;
    envp = (char **)ft_calloc(map.size + 1, sizeof(char *));
    i.start = 0;
    i.end = 0;
    while (i.start < TABLE_SIZE)
    {
        current = map.table[i.start];
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
