#include "ft_minishell.h"

void	redir_sig()
{
	signal(SIGINT, sigint_r);
	signal(SIGQUIT, sigquit_r);
	kill(0, SIGUSR1);
}

void	check_heredock(t_redir *redirs, t_node *cur_cmd)
{
	int	pid;
	
	while (redirs != NULL)
	{
		if (redirs->type == REDIRECT_DOUBLE_LEFT)
		{
			pid = fork();
			if (pid == 0)
				double_left(redirs, cur_cmd);
			waitpid(0, 0, 0);
		}
		redirs = (t_redir *)redirs->next;
	}
}