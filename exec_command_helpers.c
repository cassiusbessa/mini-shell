#include "minishell.h"

static void	update_last_status(t_hashmap *envs, int status);

void	pre_exec(t_token_lst *lst)
{
	unquotes_all_words(lst);
	pipe_all_cmds(lst);
	redir_all_cmds(lst);
}

void	update_status(int status, t_hashmap *envs)
{
	if (WIFSIGNALED(status))
		update_last_status(envs, 128 + WTERMSIG(status));
	if (WIFEXITED(status))
		update_last_status(envs, WEXITSTATUS(status));
}

static void	update_last_status(t_hashmap *envs, int status)
{
	char	*str;

	str = ft_itoa(status);
	insert_pair(&envs, create_pair("?", str));
	free(str);
}