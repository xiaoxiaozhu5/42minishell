#include "ft_minishell.h"

char	*find_path1(t_env *data, t_node *iter)
{
	struct stat	buff;
	char		*needed_cmd;
	int			i;
	int			res;

	i = 0;
	res = stat(iter->command, &buff);
	if (res == 0 && (buff.st_mode))
	{
		return (iter->command);
	}
	needed_cmd = iter->command;
	while (data->execve_paths[i])
	{
		res = stat(needed_cmd, &buff);
		if (res == 0 && (buff.st_mode))
			return (needed_cmd);
		needed_cmd = ft_strjoin(data->execve_paths[i], "/");
		needed_cmd = ft_strjoin(needed_cmd, iter->command);
		i++;
	}
	return (NULL);
}

static int	**allocate_ar_of_fds_and_pid(int n_pipes, int **pid)
{
	int	**fds;
	int	i;

	i = 0;
	fds = malloc(sizeof(int *) * (n_pipes + 1));
	if (!fds)
		return (NULL);
	while (i < n_pipes)
	{
		fds[i] = (int *) malloc(sizeof (int) * 2);
		if (!fds[i])
			return (NULL);
		pipe(fds[i]);
		i++;
	}
	fds[i] = (int *) malloc(sizeof (int) * 2);
	pipe(fds[i]);
	*pid = (int *)malloc(sizeof(int) * (n_pipes + 1));
	return (fds);
}

static void	close_open_things(int i, int *pid, int **p, int pipes)
{
	if (pid[i] == 0 && i == 0)
	{
		close(p[i][0]);
		dup2(p[i][1], 1);
	}
	else if (i != pipes)
	{
		close(p[i - 1][1]);
		dup2(p[i - 1][0], 0);
		close(p[i][0]);
		dup2(p[i][1], 1);
	}
	else if (i == pipes)
	{
		close(p[i - 1][1]);
		dup2(p[i - 1][0], 0);
	}
}

static void	pipe_v2(int i, int *pid, int **p, int pipes, t_env *data, t_node *iter)
{
	if (pid[i] > 0)
	{
		close(p[i][1]);
	}
	else if (pid[i] == 0)
	{	
		if (iter->redirs != NULL)
		{
			make_redirrect(iter, data);
		}
		else
		{
			close_open_things(i, pid, p, pipes);
			ft_execve(data, iter);
		}
	}
}

void	ft_new_pipe(t_env *data)
{
	int		**p;
	int		*pid;
	int		i;
	int		pipes;
	t_node	*iter;

	p = allocate_ar_of_fds_and_pid(data->n_pipes, &pid);
	iter = data->cmds;
	pipes = data->n_pipes;
	i = 0;
	while (i <= pipes)
	{
		pid[i] = fork();
		pipe_v2(i, pid, p, pipes, data, iter);
		iter = iter->next;
		i++;
	}
	while (i--)
	{
		waitpid(0, 0, 0);
	}
}
