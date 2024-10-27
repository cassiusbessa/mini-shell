#include "minishell.h"

int	pwd_cmd(t_main  *main)
{
	char	*pwd;

	pwd = get_value(main->envs, "PWD");
	if (!pwd)
		return (0);
	printf("%s\n", pwd);
	return (1);
}