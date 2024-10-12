#include "minishell.h"
#include <signal.h>

static void	handle_sigaction(int signum, siginfo_t *info, void *context)
{
	if (signum == 2 && info->si_pid == 0)
		exit(130);
	else
	{
		write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay(); 
	}

}

void	setup_sigaction_handler(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO; // Usa sa_sigaction para mais informações
	sa.sa_sigaction = handle_sigaction;

	sigaction(SIGINT, &sa, NULL);
}
