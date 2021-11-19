#include "../includes/ft_minishell.h"
#include <string.h>
#include <sys/stat.h>
// #include <limits.h>
#include <sys/wait.h>
//#define WEXITSTATUS(x)  ((_W_INT(x) >> 8) & 0x000000ff)
int		exit_status;


char *find_path1(t_env *data, t_node *iter)
{
	struct stat	buff;
	char *needed_cmd;
	int	i = 0;
	int res;
	while(data->execve_paths[i])
	{
		needed_cmd = ft_strjoin(data->execve_paths[i], "/");
		needed_cmd = ft_strjoin(needed_cmd, iter->command);
		res = stat(needed_cmd, &buff);
		if (res == 0 && (buff.st_mode))
			return needed_cmd;
		i++;
	}
	return(NULL);
}

typedef struct pid_s
{
	pid_t pid;
	int		status;
} pidt;

static int **allocate_ar_of_fds_and_pid(int n_pipes, int **pid)
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
	return(fds);
}

void	ft_new_pipe(t_env *data)
{
	int	**p;

	int	*pid;
	int		i = 0;
	int		pipes;
	t_node *iter;
	p = allocate_ar_of_fds_and_pid(data->n_pipes, &pid);
	iter = data->cmds;
	pipes = data->n_pipes;
	while(i <= pipes)
	{
		pid[i] = fork();
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
				
				// if ((ft_execve(data, iter)) == -1)
					// kill(pid[i], 0);
				ft_execve(data, iter);
			}
		}
		iter = iter->next;
		i++;
	}
	while(i--)
	{
		waitpid(0, 0 , 0);
	}
	// exit(0);
	// sleep(4);
// int ier = 0;

// while (ier < 3)
// {
// 	wait(0);
// 	ier++;
// }
// while(1);
}


// int main (int ac, char **av, char **env)
// {
// 	t_data data;

// 	ft_new_pipe(&data, env);
// }

