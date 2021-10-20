#include "../includes/ft_minishell.h"

void	right_redirrect(t_env *a, t_data *data)
{
	int		fd;
	char	*some_THING;

	some_THING = "hellooooou\n";
	int i = 0;
	// if (str[i] == '>')
	// {
	// 	i++;
		if (data->redirr_type[1] == '>')
			fd = open(data->file_name, O_WRONLY | O_CREAT| O_APPEND, 0644);
		else
			fd = open(data->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, ft_echo(data), ft_strlen(data->str));
}

void	exec_cmd(t_data *data)
{
	
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
				heredock = readline("heredock> ");
				if ((ft_cmp(heredock, data->file_name)) == 0)
				{
					// exec_cmd(data);
					break;
				}
			}
		}
		// return ;
		or_or = 0;
	}
	fd = open(data->file_name, O_RDONLY, 0644);
	if (or_or == 1)
	{
		if (fd == -1)
		{
			write(1, "no such file or directory: ",
				ft_strlen("no such file or directory: "));
			ft_putstr_fd(data->file_name, 1);
			write(1, "\n", 1);
		}
		else
			execlp("ls", "-a", NULL);//нужно записать в файл результат выполнения команды
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

void	ft_redir(t_env *a, t_data *data)
{
	int	red_left_or_right;
	int	i;

	i = 0;
	if (data->redirr_type[0] == '<')
		red_left_or_right = 1;
	else if (data->redirr_type[0] == '>')
		red_left_or_right = 0;
	choose_right(a, data, red_left_or_right);
	
}

int main(int ac, char **av)
{
	// char	*a;
	t_data	*data;

	data = malloc(sizeof(*data));
	data->cmd = malloc(sizeof(char) * ft_strlen(av[1]));
	data->str = malloc(sizeof(char) * ft_strlen(av[2] + 1));
	data->redirr_type = malloc(sizeof(char) * ft_strlen(av[3]));
	data->file_name = malloc(sizeof(char) * ft_strlen(av[4]));
	data->cmd = av[1];
	data->str = av[2];
	data->redirr_type = av[3];
	data->file_name = av[4];
	data->flag = NULL;
	ft_redir(NULL, data);
}