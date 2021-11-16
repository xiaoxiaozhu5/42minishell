#include "../includes/ft_minishell.h"

// int	exec_cmd1(t_node *data, int fd, t_env *a)
// {
// 	// char	**a;
// 	int		i;
// 	char	*needed_cmd;

// 	int	ew;
// 	i = 0;
// 	// int pides;
// 	// some subj cmd//
// 	//....//
// 	// fd = 1;
// 	// if (pides == 0)
// 	// {
// 		dup2(fd, 1);
// 		while (a->execve_paths[i] != NULL)
// 		{
// 			needed_cmd = ft_strjoin(a->execve_paths[i], "/");
// 			needed_cmd= ft_strjoin(needed_cmd, data->command);
// 			// puts(data->flags[0]);
// 			if ((ew = execve(needed_cmd, data->exec_args, a->envp)) == -1)
// 				i++;
// 			else
// 			{
// 				break ;
// 			}
// 			free(needed_cmd);
// 			// printf("%d\n", ew);
// 		// }
// 		// if(pides != 0)
// 		// {
// 			// kill(pides, 1);
// 		// }
// 	}
// 		return (0);
// }

// void	right_redirrect(t_redir *cur_redir, t_node *data)
// {
// 	int		fd;
// 	int		i;
	
// 	// (void)a;
// 	i = 0;
// 		if (cur_redir->type == REDIRECT_DOUBLE_RIGHT)
// 		{
// 			fd = open(cur_redir->value, O_WRONLY | O_CREAT| O_APPEND, 0644);
// 			dup2(data->redir_1, fd);
// 		}
// 		else
// 		{
// 			fd = open(cur_redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			dup2(data->redir_1, fd);
// 		}
// 	// if (exec_cmd1(data, fd, a) == 1)
// 	// {
// 	// 	// write(fd, ft_echo(data), ft_strlen(data->str));
// 	// 	//сделать для пипов
// 	// }
// 	// TODO переписать фдшники
// }


// void	left_redirrect(t_redir *cur_redir, t_node *data)
// {
// 	int	fd;
// 	// int	or_or = 1;
// 	char *heredock;
// 	pid_t pid;


// 	if (cur_redir->type == REDIRECT_DOUBLE_LEFT)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			while (1)
// 			{
// 				heredock = readline("> ");
// 				if ((ft_cmp(heredock, cur_redir->value)) == 0)
// 				{
// 					exec_cmd1(data, -1, a);
// 					break;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			kill(pid, 15);
// 		}
// 	}
// 	else
// 	{
// 		fd = open(cur_redir->value, O_RDONLY, 0644);
// 		if (fd == -1)
// 		{
// 			write(1, "no such file or directory: ", 29);
// 			ft_putstr_fd(cur_redir->value, 1);
// 			write(1, "\n", 1);
// 		}
// 		else
// 		{
// 			// exec_cmd1(data, fd, a);
// 			// execlp("ls", "-a", NULL);//нужно записать в файл результат выполнения команды
// 		}
// 	}
// }

// void	choose_redirrect(t_node *a, t_redir *b)
// {
// 	t_redir	*cur_redir;

// 	cur_redir = NULL;
	
// 	if (b->type == REDIRECT_LEFT || b->type == REDIRECT_DOUBLE_LEFT)
// 	{
// 		left_redirrect(cur_redir, a);
// 	}
// 	else
// 	{
// 		puts("GOOD");
// 		right_redirrect(cur_redir, a);
// 	}
// }

// // void	ft_redir(t_env *a, t_node *data)
// // {
// // 	int	red_left_or_right;
// // 	int	i;

// // 	i = 0;
// // 	// if (data->redirr_type[0] == '<')
// // 	// 	red_left_or_right = 1;
// // 	// else if (data->redirr_type[0] == '>')
// // 	// 	red_left_or_right = 0;
// // 	choose_right(a, data, red_left_or_right);
	
// // }

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

static void simple_right(t_redir *redir, t_node *cmd_info)
{
	int	fd;
	// (void)cmd_info;
	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, cmd_info->redir_1);//(1)
	// dup2(0, fd);
}

static void double_right(t_redir *redir, t_node *cmd_info)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT| O_APPEND, 0644);
	dup2(cmd_info->redir_1, fd);
}

static int simple_left(t_redir *redir, t_node *cmd_info)
{
	int	fd;

	fd = open(redir->value, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(1, "no such file or directory: ", 29);
		ft_putstr_fd(redir->value, 1);
		write(1, "\n", 1);
		printf("%s: no such file or directory\n", redir->value);
		return (-1);
	}
	else
	{
		dup2(cmd_info->redir_0, fd);
		return 1;
	}
}

static int double_left(t_redir *redir, t_node *cmd_info)
{
	int		pid;
	char	*heredock;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			heredock = readline("> ");
			if ((ft_strcmp(heredock, redir->value)) == 0)
			{
				break;
			}
		}
		exit(-1);
	}
	waitpid(-1, 0, 0);
	dup2(cmd_info->redir_1, cmd_info->fds[1]);
	return 1;
}

static void choose_redirrect(t_redir *redirs, t_node *cmd)
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
		simple_left(redirs, cmd);
	}
	else if (redirs->type == REDIRECT_DOUBLE_LEFT)
	{
		double_left(redirs, cmd);
	}
}

void	make_redirrect(t_node *cur_cmd, t_env *env)
{
	t_redir	*redirs;

	redirs = (t_redir *)cur_cmd->redirs;
	while (redirs != NULL)
	{
		choose_redirrect(redirs, cur_cmd);
		redirs = (t_redir *)redirs->next;
	}
}