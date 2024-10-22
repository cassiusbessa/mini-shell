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

	tmp = main->token_lst->head;

	while (tmp->next)
	{
		
		if (!ft_strcmp(tmp->word, "env"))
			tmp = tmp->next;
		else
		{
			error_env(tmp->word);
			last_status(127);
			return (0);
		}
	}
	while (main->envs->table)
	{
		printf("%s\n", main->envs->table);
	}
	printf("aq\n");
	last_status(0);
	return (1);
}