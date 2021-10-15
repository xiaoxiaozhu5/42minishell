~~~#include "../includes/ft_minishell.h"


void	right_redirrect(t_env *a, char *str)
{

}

void	left_redirrect(t_env *a, char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(1, "no such file or directory: ",
			ft_strlen("no such file or directory: "));
		ft_putstr_fd(str + 1, 1);
	}
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
	
}

int main(int ac, char **av)
{
	ft_redir(NULL, av[1]);
}