#include "../includes/ft_minishell.h"

// void	sigint(int signal)
// {
// 	(void)signal;
// 	exit(130);
// }

// void	sigquit(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	exit(130);
// }

static int	double_left(t_redir *redir, t_node *cmd_info)
{
	int		pid;
	char	*heredock;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_r);
		signal(SIGQUIT, sigquit_r);
		kill(0, SIGUSR1);
		while (1)
		{
			heredock = readline("heredock> ");
			if (!heredock)
			{
				printf("heredock> %s\n", redir->value);
				exit(0);
			}
			if ((ft_strcmp(heredock, redir->value)) == 0)
				break ;
		}
		exit(0);
	}
	waitpid(0, 0, 0);
	exit(0);
	(void) cmd_info;
	return (1);
}

static void	choose_redirrect(t_redir *redirs, t_node *cmd)
{
	if (redirs->type == REDIRECT_RIGHT)
	{
		simple_right(redirs, cmd);
	}
	else if (redirs->type == REDIRECT_DOUBLE_RIGHT)
	{
		double_right(redirs, cmd);
	}
	else if (redirs->type == REDIRECT_LEFT)
	{
		if (simple_left(redirs, cmd) == -1)
		{
			exit(0);
		}
	}
}

static int	check_redirs(t_node *cur_cmd, t_redir	*redirs)
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
	redirs = (t_redir *)cur_cmd->redirs;
	while (redirs != NULL)
	{
		if (redirs->value[0] == '\0')
		{
			printf("error!\n");
			if (cur_cmd->next == NULL)
				return (-1);
			exit (-1);
		}
		redirs = (t_redir *)redirs->next;
	}
	return (0);
}

static void	all_redir_things(t_node *cur_cmd, t_env *env)
{
	t_redir	*redirs;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		redirs = (t_redir *)cur_cmd->redirs;
		while (redirs != NULL)
		{
			choose_redirrect(redirs, cur_cmd);
			redirs = (t_redir *)redirs->next;
		}
		ft_execve(env, cur_cmd);
		exit(0);
	}
	waitpid(0, 0, 0);
	if (env->n_pipes > 0)
		exit(0);
}

void	make_redirrect(t_node *cur_cmd, t_env *env)
{
	t_redir	*redirs;

	redirs = (t_redir *)cur_cmd->redirs;
	if (check_redirs(cur_cmd, redirs) == -1)
		return ;
	redirs = (t_redir *)cur_cmd->redirs;
	cur_cmd->fds[1] = 2;
	cur_cmd->fds[1] = dup(cur_cmd->redir_1);
	if (cur_cmd->redirs != NULL)
	{
		all_redir_things(cur_cmd, env);
	}
	else
		ft_execve(env, cur_cmd);
}
