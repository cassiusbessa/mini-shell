#include "minishell.h"

void	env_cmd(char **token)
{
	int	i;
	char	**env;

	if (token[1])
	{
		//| Tem que dar erro porque ENV não aceita nenhuma flag.
		printf("Error!\n","\tenv does not accept flags.\n");
		return ;
	}
	env = static_env(NULL, NOFREE);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}