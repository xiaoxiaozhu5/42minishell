#include "../includes/ft_minishell.h"

int	exec_cmd(t_data *data)
{
	char	**a;
	int		i;
	char	*needed_cmd;

	int	ew;
	i = 0;
	if (ft_cmp("echo", data->cmd) == 0)
	{
		data->str = ft_echo(data);
		return (1);
	}
	// some subj cmd//
	//....//
	else
	{
		dup2(data->fd, 1);
		while (data->path[i])
		{
			needed_cmd= ft_strjoin(data->path[i], data->cmd);
			puts(data->flags[0]);
			if ((ew = execve(needed_cmd, data->flags, data->env)) == -1)
				i++;
			else
			{
				break ;
			}
			free(needed_cmd);
			printf("%d\n", ew);
		}
		return (0);
	}
}

void	right_redirrect(t_env *a, t_data *data)
{
	int		fd;
	int i;
	
	i = 0;
		if (data->redirr_type[1] == '>')
			data->fd = open(data->file_name, O_WRONLY | O_CREAT| O_APPEND, 0644);
		else
			data->fd = open(data->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_cmd(data) == 1)
	{
		write(fd, ft_echo(data), ft_strlen(data->str));
		//сделать для пипов
	}
}


void	left_redirrect(t_env *a, t_data *data)
{
	int	fd;
	int	or_or = 1;
	char *heredock;
	pid_t pid;


	if (data->redirr_type[1] == '<')
	{
		pid = fork();
		if (pid == 0)
		{
			while (1)
			{
				heredock = readline("> ");
				if ((ft_cmp(heredock, data->file_name)) == 0)
				{
					exec_cmd(data);
					break;
				}
			}
		}
		or_or = 0;
	}
	data->fd = open(data->file_name, O_RDONLY, 0644);
	if (or_or == 1)
	{
		if (fd == -1)
		{
			write(1, "no such file or directory: ", 29);
			ft_putstr_fd(data->file_name, 1);
			write(1, "\n", 1);
		}
		else
		{
			exec_cmd(data);
			// execlp("ls", "-a", NULL);//нужно записать в файл результат выполнения команды
		}
	}
	while(1);
}

void	choose_right(t_env *a, t_data *data, int flag)
{
	if (flag == 1)
		left_redirrect(a, data);
	if (flag == 0)
		right_redirrect(a, data);
}

void	ft_redir(t_env *a, t_node *data)
{
	int	red_left_or_right;
	int	i;

	i = 0;
	// if (data->redirr_type[0] == '<')
	// 	red_left_or_right = 1;
	// else if (data->redirr_type[0] == '>')
	// 	red_left_or_right = 0;
	choose_right(a, data, red_left_or_right);
	
}

////////////////////////////////////////////////////////////////////////////
void	some_inits_1(t_data *data)
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
	data->commands[2][0] = "pwd";
	data->commands[2][1] = NULL;
	data->commands[2][2] = NULL;
}
////////////////////////////////////////////////////////////////////////////

int main(int ac, char **av, char **env)
{
	// char	*a;
	t_data data;
	some_inits_1(&data);
	fill_env_path(&data, env);
	
}