#include "../includes/ft_minishell.h"

int	exec_cmd1(t_node *data, int fd, t_env *a)
{
	// char	**a;
	int		i;
	char	*needed_cmd;

	int	ew;
	i = 0;
	// some subj cmd//
	//....//
	fd = 1;
		// dup2(1, fd);
		while (a->execve_paths[i] != NULL)
		{
			needed_cmd= ft_strjoin(a->execve_paths[i], data->command);
			// puts(data->flags[0]);
			if ((ew = execve(needed_cmd, data->exec_args, a->envp)) == -1)
				i++;
			else
			{
				break ;
			}
			free(needed_cmd);
			// printf("%d\n", ew);
		}
		return (0);
}

void	right_redirrect(t_redir *cur_redir, t_node *data, t_env *a)
{
	int		fd;
	int		i;
	
	i = 0;
		if (cur_redir->type == REDIRECT_RIGHT)
			fd = open(cur_redir->value, O_WRONLY | O_CREAT| O_APPEND, 0644);
		else
			fd = open(cur_redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_cmd1(data, fd, a) == 1)
	{
		// write(fd, ft_echo(data), ft_strlen(data->str));
		//сделать для пипов
	}
}


void	left_redirrect(t_redir *cur_redir, t_node *data, t_env *a)
{
	int	fd;
	// int	or_or = 1;
	char *heredock;
	pid_t pid;


	if (cur_redir->type == REDIRECT_DOUBLE_LEFT)
	{
		pid = fork();
		if (pid == 0)
		{
			while (1)
			{
				heredock = readline("> ");
				if ((ft_cmp(heredock, cur_redir->value)) == 0)
				{
					exec_cmd1(data, -1, a);
					break;
				}
			}
		}
	}
	else
	{
		fd = open(cur_redir->value, O_RDONLY, 0644);
		if (fd == -1)
		{
			write(1, "no such file or directory: ", 29);
			ft_putstr_fd(cur_redir->value, 1);
			write(1, "\n", 1);
		}
		else
		{
			exec_cmd1(data, fd, a);
			// execlp("ls", "-a", NULL);//нужно записать в файл результат выполнения команды
		}
	}
}

void	choose_redirrect(t_env *a)
{
	t_redir	*cur_redir;

	cur_redir = NULL;
	if (a->cmds->redirs != NULL)
	{
		cur_redir = (t_redir *)a->cmds->redirs;
	}
	if (cur_redir->type == REDIRECT_LEFT || cur_redir->type == REDIRECT_DOUBLE_LEFT)
	{
		left_redirrect(cur_redir, a->cmds, a);
	}
	else
	{
		right_redirrect(cur_redir, a->cmds, a);
	}
}

// void	ft_redir(t_env *a, t_node *data)
// {
// 	int	red_left_or_right;
// 	int	i;

// 	i = 0;
// 	// if (data->redirr_type[0] == '<')
// 	// 	red_left_or_right = 1;
// 	// else if (data->redirr_type[0] == '>')
// 	// 	red_left_or_right = 0;
// 	choose_right(a, data, red_left_or_right);
	
// }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////