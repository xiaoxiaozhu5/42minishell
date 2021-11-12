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
	data->commands[2][0] = "cat";
	data->commands[2][1] = "-e";
	data->commands[2][2] = NULL;
}
char *find_path1(t_env *data, t_node *iter)
{
	struct stat	buff;
	char *needed_cmd;
	int	i;
	int res;
	i = 0;
	while(data->execve_paths[i] != NULL)
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


void	ft_new_pipe(t_env *data)
{
	int	p[2][2];

	pipe(p[0]);
	pipe(p[1]);
	pid_t	pid[2];
	int	i = 0;
	char *cmd;
	int		pipes;
	t_node *iter;

	iter = data->cmds;
	pipes = data->n_pipes;
	while(i <= pipes)
	{
		cmd = ft_strdup(find_path1(data, iter));
		pid[i] = fork();
		if (pid[i] > 0)
		{
			close(p[i][1]);
		}
		if (pid[i] == 0)
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
				//команда для чпроверки наша или нет
				execve(cmd, iter->args, data->envp);//ls, [{ls}]
			}
			if ((execve(cmd, iter->args, data->envp)) == -1)
				kill(pid[i], SIGTERM);
			// data->cmds->args = data->cmds->next;
		}
		iter = iter->next;
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


// int main (int ac, char **av, char **env)
// {
// 	t_data data;

// 	ft_new_pipe(&data, env);
// }

