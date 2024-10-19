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
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_sigaction_main;
	sigaction(SIGINT, &sa, NULL);
}

void	setup_sigaction_child(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	// sa.sa_sigaction = SIG_DFL;
	sa.sa_handler = SIG_DFL;

	sigaction(SIGINT, &sa, NULL);
}
