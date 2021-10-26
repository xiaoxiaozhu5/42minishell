#include "../includes/ft_minishell.h"
#include <string.h>
#include <sys/stat.h>

void	exec_pipe(t_data *data, char *cmd)
{
	close(data->fds[0]);
	dup2(data->fds[1], 1);
	execve(cmd, data->args, data->env);
	почти реализовал пайпы
}

void	pipe_realise(t_data *data)
{
	int			res;
	int			i, ew;
	char		needed_cmd;
	struct stat	buff;
	char		*sec_cmd = "cat";
	char **sec_cmd = malloc(sizeof(char **) * 3);
	sec_cmd [0] = malloc(10);
	sec_cmd[0] = "ls\0";
	sec_cmd[1] = NULL;

	i = 0;
	while (data->path[i])
	{
		needed_cmd = ft_strjoin(data->path[i], data->cmd);
		puts(data->flags[0]);

		res = stat(needed_cmd, &buff);
		if (res == 0 && (buff.st_mode))
			exec_pipe(data, needed_cmd);
		//free(needed_cmd);
		printf("%d\n", ew);
	}
}

void	ft_pipe(t_data *data)
{
	char **args;
	char *a = "ls";
	args = malloc(sizeof(char **) * 3);
	args[0] = "ls";
	args[1] = NULL;
	data->args = malloc(sizeof(char **) * 3);
	data->args[0] = ft_strdup(args[0]);
	if (data->pipe != 0)
	{
		if (pipe(data->fds) == -1)
			printf("errrrror pipe");
		data->pid = fork();
		if (data->pid == -1)
			printf("error pid");
		if (data->pid > 0)
		{
			close (data->fds[1]);
		}
		else
			pipe_realise(data);
		dup2(data->fds[0], 0);
		dup2(data->fds[1], 1);
	}
}

int main (int ac, char **av, char **env)
{
	t_data data;

	fill_env_path(&data, env);
	ft_pipe(&data);
}


// int main(int argc, char *argv[])
// {
// 	int pipefd[2];
//     pid_t cpid;
//     char buf;

//     if (argc != 2)
// 	{
//     	fprintf(stderr, "Usage: %s <string>\n", argv[0]);
// 		exit(EXIT_FAILURE);
//     }
//     if (pipe(pipefd) == -1) 
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	cpid = fork();
// 	if (cpid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cpid == 0)
// 	{    /* Child reads from pipe */
// 		close(pipefd[1]);          /* Close unused write end */
// 		while (read(pipefd[0], &buf, 1) > 0)
// 			write(STDOUT_FILENO, &buf, 1);
// 		write(STDOUT_FILENO, "\n", 1);
// 		close(pipefd[0]);
// 		_exit(EXIT_SUCCESS);
//     }
// 	else
// 	{            /* Parent writes argv[1] to pipe */
// 		close(pipefd[0]);          /* Close unused read end */
//  		write(pipefd[1], argv[1], strlen(argv[1]));
//                close(pipefd[1]);          /* Reader will see EOF */
//                wait(NULL);                /* Wait for child */
//                exit(EXIT_SUCCESS);
//            }
//        }