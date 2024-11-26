/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 01:42:07 by cassius           #+#    #+#             */
/*   Updated: 2024/11/11 01:42:12 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cmd(t_main *main)
{
	char				*output;

	output = getcwd(NULL, 0);
	ft_putendl_fd(output, main->token_lst->head->fd[1]);
	free(output);
	return (1);
}
