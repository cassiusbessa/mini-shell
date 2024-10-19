#include "minishell.h"

int is_number(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

int only_number(char *word)
{
	int i;

	i = 0;
	if (word[i] == '-')
		return (0);
	if (word[i] == '+')
		i++;
	while (word[i])
		if (!is_number(word[i++]))
			return (0);
	return (1);
}

long long ft_atoll(const char *nptr)
{
	long long nb;
	int mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}

int is_long(char *word)
{
	if (ft_strlen(word) > 20 || ft_atoll(word) > LONG_MAX || ft_atoll(word) < LONG_MIN)
		return (0);
	return (1);
}

void	exit_cmd(t_token_lst *lst)
{
	t_token	*tmp;

	tmp = lst->head->next;
	if (tmp && (!only_number(tmp->word) || !is_long(tmp->word)))
	{
		//TODO: 
		// APAGAR ENVS
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n",tmp->word);
		exit(1);
	}
	if (tmp && tmp->next)
	{
		//TODO: 
		// APAGAR ENVS
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		exit(1);
	}
	//TODO: 
		// APAGAR ENVS
	printf("exit\n");
	exit(1);
}

int	check_flag(t_token *token)
{
	if (!ft_strcmp(token->word, "-n"))
		return (1);
	return (0);
}

void	echo_cmd(t_main *main)
{
	int	i;
	int	space;
	int	newline;
	t_token	*tmp;

	tmp = main->token_lst->head->next;
	newline = 1;
	while (check_flag(tmp))
	{
		tmp = tmp->next;
		newline = 0;
	}
	space = 0;
	while (tmp)
	{
		if (space)
			printf(" ");
		else
			space++;
		printf("%s", tmp->word);
		tmp = tmp->next;
	}
	if (newline)
		printf("\n");
}

int	builtins(t_main *main)
{
	if (!ft_strcmp(main->token_lst->head->word, "exit"))
		return(exit_cmd(main->token_lst), 1);
	/*else if (!ft_strcmp(main->token_lst, "env"))
		return(env_cmd(main->token_lst), 1);
	else if (!ft_strcmp(main->token_lst, "pwd"))
		return(pwd_cmd(), 1);*/
	else if (!ft_strcmp(main->token_lst->head->word, "echo"))
		return(echo_cmd(main), 1);
	else if (!strcmp(main->token_lst->head->word, "cd"))
		return(cd_cmd(main), 1);
	/*else if (!strcmp(main->token_lst, "export"))
		export_cmd(main->token_lst);*/
	/*else if (!ft_strcmp(main->token_lst, "unset"))
		unset_cmd(main->token_lst);*/
return (0);
}