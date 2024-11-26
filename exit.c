/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymometto <ymometto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:12:21 by ymometto          #+#    #+#             */
/*   Updated: 2024/11/11 13:12:40 by ymometto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

int	only_number(char *word)
{
	int	i;

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

long long	ft_atoll(const char *nptr)
{
	long long	nb;
	int			mult;

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

int	is_long(char *word)
{
	if (ft_strlen(word) > 20 || ft_atoll(word) > LONG_MAX
		|| ft_atoll(word) < LONG_MIN)
		return (0);
	return (1);
}

void	exit_cmd(t_token_lst *lst)
{
	t_token	*tmp;

	tmp = lst->head->next;
	if (tmp && (!only_number(tmp->word) || !is_long(tmp->word)))
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", tmp->word);
		exit(1);
	}
	if (tmp && tmp->next)
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		exit(1);
	}
	printf("exit\n");
	exit(1);
}