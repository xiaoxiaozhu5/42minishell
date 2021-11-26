#include "../includes/ft_minishell.h"

void	simple_right(t_redir *redir, t_node *cmd_info)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, cmd_info->redir_1);
}

void	double_right(t_redir *redir, t_node *cmd_info)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, cmd_info->redir_1);
}

int	simple_left(t_redir *redir, t_node *cmd_info)
{
	int	fd;

	fd = open(redir->value, O_RDONLY, 0644);
	if (fd == -1)
	{
		dup2(cmd_info->fds[1], cmd_info->redir_1);
		printf("%s: no such file or directory\n", redir->value);
		return (-1);
	}
	else
	{
		dup2(fd, cmd_info->redir_0);
		return (1);
	}
}

void	sigint_r(int signal)
{
	(void)signal;
	exit(130);
}

void	sigquit_r(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	exit(130);
}

