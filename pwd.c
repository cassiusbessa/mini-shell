#include "minishell.h"

int	pwd_cmd(t_main *main)
{
	char				*output;

	output = getcwd(NULL, 0);
	ft_putendl_fd(output, main->token_lst->head->fd[2]);
	free(output);
	return (1);
}