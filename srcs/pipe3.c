#include "../includes/ft_minishell.h"
#include <string.h>
#include <sys/stat.h>
// #include <limits.h>
#include <sys/wait.h>
#define WEXITSTATUS(x)  ((_W_INT(x) >> 8) & 0x000000ff)
int		exit_status;

void	some_inits(t_data *data)
{
	data->count_pipes = 1;
	//init 2 commands
	data->commands = malloc(sizeof(char ***) * 3);
	data->commands[0] = malloc(sizeof(char **) * 4);
	data->commands[1] = malloc(sizeof(char **) * 4);
	data->commands[2] = malloc(sizeof(char **) * 4);
	data->commands[3] = NULL;
	data->commands[0][0] = "ls";
	data->commands[0][1] = NULL;
	data->commands[1][0] = "cat";
	data->commands[1][1] = "-e";
	data->commands[1][2] = NULL;
	// data->commands[2][0] = "cat";
	// data->commands[2][1] = "-e";
	// data->commands[2][2] = NULL;
	data->commands[2][0] = "pwd";
	data->commands[2][1] = NULL;
	data->commands[2][2] = NULL;
}
char *find_path1(t_data *data, int k)
{
	struct stat	buff;
	char *needed_cmd;
	int	i;
	int res;
	i = 0;
	while(data->path[i] != NULL)
	{
		needed_cmd = ft_strjoin(data->path[i], data->commands[k][0]);
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


void	ft_new_pipe(t_data *data, char **env)
{
	fill_env_path(data, env);
	some_inits(data);
	int	p[2][2];

	pipe(p[0]);
	pipe(p[1]);
	pidt	pid[2];
	int	i = 0;
	char *cmd;
	int		pipes;

	pipes = 2;
	while(i <= pipes)
	{
		cmd = ft_strdup(find_path1(data, i));
		pid[i].pid = fork();
		if (pid[i].pid > 0)
		{
			close(p[i][1]);
		}
		if (pid[i].pid == 0)
		{	
			if (pid[i].pid == 0 && i == 0)
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
				
				execve(cmd, data->commands[i], env);
			}
			if ((execve(cmd, data->commands[i], env)) == -1)
				kill(pid[i].pid, SIGTERM);
		}
		i++;
	}
// int ier = 0;

// while (ier < 3)
// {
// 	wait(0);
// 	ier++;
// }
// while(1);
}


int main (int ac, char **av, char **env)
{
	t_data data;

	ft_new_pipe(&data, env);
}

