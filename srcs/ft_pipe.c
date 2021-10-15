#include "../includes/ft_minishell.h"

// void	pipes(t_env *a)
// {

// }
int main (int ac, char **av, char **env)
{
	int	fd[2];
	char **a;

	// a = malloc (sizeof(char *) * 2);
	// a[0] = malloc(sizeof("usr/bin/zsh/ls"));
	// a[2] = malloc(sizeof("-a"));

	if (pipe(fd) == -1)
		return (1);
	
	int pid1 = fork();

	if (pid1 == 0)
	{
		execve("usr/bin/ls", av, env);
	}
	waitpid(pid1, NULL, 0);
}