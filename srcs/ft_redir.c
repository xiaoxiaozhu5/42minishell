#include "../includes/ft_minishell.h"

void	right_redirrect(t_env *a, char *str)
{
	int		fd;
	char	*some_THING;

	some_THING = "hellooooou\n";
	int i = 0;
	if (str[i] == '>')
	{
		i++;
		if (str[i] == '>')
		{
			i++;
			fd = open(str + 2, O_WRONLY | O_CREAT| O_APPEND, 0644);
		}
		else
			fd = open(str + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	printf("%d\n", fd);
	write(fd, some_THING, ft_strlen(some_THING));
}

void	left_redirrect(t_env *a, char *str)
{
	int	fd;

	fd = open(str+1, O_RDONLY, 0644);
	if (fd == -1)
	{
		write(1, "no such file or directory: ",
			ft_strlen("no such file or directory: "));
		ft_putstr_fd(str + 1, 1);
		write(1, "\n", 1);
	}
	else
		execlp("ls", "-a", NULL);
}

void	choose_right(t_env *a, char *str, int flag)
{
	if (flag == 1)
		left_redirrect(a, str);
	if (flag == 0)
		right_redirrect(a, str);
}

void	ft_redir(t_env *a, char *str)
{
	int	red_left_or_right;
	int	i;

	i = 0;
	if (str[i] == '<')
		red_left_or_right = 1;
	else if (str[i] == '>')
		red_left_or_right = 0;
	choose_right(a, str, red_left_or_right);
	
}

int main(int ac, char **av)
{
	// puts(av[1]);
	ft_redir(NULL, av[1]);
}