#include "ft_minishell.h"

void	redir_sig()
{
	signal(SIGINT, sigint_r);
	signal(SIGQUIT, sigquit_r);
	kill(0, SIGUSR1);
}