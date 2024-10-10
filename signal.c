#include "minishell.h"
#include <signal.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\nminishell% ", 12);
}

void	setup_sigint_handler(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_sigint;

	sigaction(SIGINT, &sa, NULL);
}