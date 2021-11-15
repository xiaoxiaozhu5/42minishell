#include "../includes/ft_minishell.h"
#include <string.h>
#include <sys/stat.h>

void	exec_pipe(t_data *data, int	**ar_fds, int i, char **cmd, char *cmde)
{
	if (i == 0)
	{
		close(data->fds[0]);
		dup2(data->fds[1], 1);
	}
	else if (i < 1)
	{
		close(ar_fds[i - 1][1]);
		dup2(ar_fds[i - 1][0], 0);
		close(ar_fds[i][0]);
		dup2(ar_fds[i][1], 1);
	}
	else
	{
		close(ar_fds[i - 1][1]);
		dup2(ar_fds[i - 1][0], 0);
	}
	execve(cmde, cmd, data->env);
}

void	pipe_realise(t_data *data, char **cmd, int pipes, int **arfds)
{
	int			res;
	int			i, ew, k;
	char		*needed_cmd;
	struct stat	buff;


	i = 0;
	k = 0;

	while (data->path[i])
	{
		needed_cmd = ft_strjoin(data->path[i], cmd[0]);
		puts(data->flags[0]);

		res = stat(needed_cmd, &buff);
		if (res == 0 && (buff.st_mode))
			exec_pipe(data, arfds, pipes, cmd, needed_cmd);
		i++;
	}
}


void	ft_pipe(t_data *data, char ***arg)
{


	int	**arfds;
	int	*pid_s;
	int pipes;
	int	al_pipes = 1;

	pipes = 0;
	if (data->pipe != 0)
	{
		arfds = arr_of_fd_and_pids(data->count_pipes, &pid_s);
		while (pipes < al_pipes)
		{
			pid_s[pipes] = fork();
			if (pid_s[pipes] > 0 && pipes != al_pipes)
				close(arfds[pipes][1]);
			else if (arfds[pipes][1] == 0)
				pipe_realise(data, arg[pipes], pipes, arfds);
			pipes++;
			dup2(data->fds[0], 0);
			dup2(data->fds[1], 1);
		}
	}
}

int main (int ac, char **av, char **env)
{
	// t_data data;
	// char ***args;

	// args = malloc(sizeof (char ***));
	// args[0] = malloc (sizeof (char **) * 10);
	// args[1] = malloc (sizeof (char **));
	// args[2] = malloc (sizeof (char **));

	// //args[0][0] = ft_strdup("ls");
	// args[0][0] = malloc(100);
	// args[0][0] = "ls";
	// args[0][1] = "ls";
	// args[0][2] = NULL;

	// args[1][0] = ft_strdup("cat");
	// args[1][1] = ft_strdup("-e");
	// args[1][2] = NULL;

	// args[2] = NULL;

	// data.pipe = 1;
	//fill_env_path(&data, env);
	//ft_pipe(&data, args);

	char **asse = malloc(sizeof (char **) * 4);
	asse[0] = ft_strdup("/bin/ls");
	asse[1] = NULL;
	execve(asse[0], asse, env);
}
static int	**arr_of_fd_and_pids(int count_pipes, int **arr_pid)
{
	int	**arr_fd;
	int	i;

	arr_fd = (int **)malloc(sizeof(int *) * (count_pipes + 1));
	if (!arr_fd)
		return (NULL);
	i = -1;
	while (++i < count_pipes)
	{
		arr_fd[i] = (int *)malloc(sizeof(int) * 2);

		pipe(arr_fd[i]);
	}
	arr_fd[i] = 0;
	*arr_pid = (int *)malloc(sizeof(int) * (count_pipes + 1));
	return (arr_fd);
}

