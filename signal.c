/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:37:51 by cassius           #+#    #+#             */
/*   Updated: 2024/11/09 19:30:29 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	handle_sigaction_main(int signum)
{
	if (RL_ISSTATE(RL_STATE_READCMD))
		ioctl(1, TIOCSTI, "\n");
	else
		write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	setup_sigaction_handler(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_sigaction_main;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_sigaction_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
}
