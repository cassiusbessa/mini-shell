#include "minishell.h"

void    free_matrix(char ***matrix)
{
        int     i;

        //| Caso não tenha matrix, só retorna.
        if (!*matrix)
                return ;
        i = -1;
        while ((*matrix)[++i])
        {
                free((*matrix)[i]); //| Free direto no endereço.
                (*matrix)[i] = NULL;//| Setando para NULL para não ter double free.
        }
        free(*matrix); //| Libera a matrix.
        *matrix = NULL;
}

char **static_env(char **new_envp, int clear)
{
        //| Static para poder acessar em outras partes do programa.
        static char **env;

        //| Caso tenha um novo ENV, limpa o antigo.
        if (new_envp && env)
                free_matrix(&env);
        //| Atualiza o antigo ENV para o novo.
        if (new_envp)
                env = new_envp;
        //| Caso precise limpar o ENV.
        if (env && clear)
                free_matrix(&env);
        return (env);
}

char *catch_env(char *find)
{
        int i;
        char **env;

        env = static_env(NULL, 0);
        i = -1;
        while (env[++i])
        {
                if (!ft_strncmp(env[i], find, ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='))))
                        return (env[i]);
        }
        return (NULL);
}

char *env_value(char *find)
{
        char *env;

        env = catch_env(find);
        if (!env)
                return (NULL);
        return (env + ft_strlen(find) + 1);
}

int	cd_cmd(t_main   *main)
{
    t_token *tmp;
	char	*path;
	char	*new_path;
	char	new_pwd[1024];

    tmp = main->token_lst->head->next;
	if (tmp && tmp->next)
		return (1);
	if (!tmp || ft_strcmp(tmp->word, "~") == 0)
	{
		path = get_value(main->envs, "HOME");
		chdir(path);
	}
	else if (ft_strcmp(tmp->word, "~") == 0)
	{
		path = get_value(main->envs, "HOME");
		if (path == NULL)
		{
			printf("cd error:%s\n", "HOME is not set");
			return (1);
		}
		new_path = ft_strjoin(path, (tmp->word + 1));
		chdir(new_path);
	}
	else
		chdir(tmp->word);
	getcwd(new_pwd, sizeof(new_pwd));
	printf("%s\n", new_pwd);
	return (0);
}