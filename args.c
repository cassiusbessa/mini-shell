#include "minishell.h"

char	**build_args(t_main *main)
{
	t_token		*tmp;
	int			i;
	char		**args;

	i = 0;
	tmp = main->token_lst->head;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND || tmp->type == ARGUMMENT)
			i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = main->token_lst->head;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND || tmp->type == ARGUMMENT)
			args[i++] = tmp->word;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
