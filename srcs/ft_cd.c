#include "../includes/ft_minishell.h"

int	ft_home_cd(t_data *data)
{
	data->args[0] = ft_strjoin("/Users/", "faggar");
	if (chdir(data->args[0]) == -1)
	{
		printf("no such file or directory");
	}
	getcwd(data->pwd_cur, MAXPATHLEN);
	puts(data->pwd_cur);
	//flag to kill proc??
	free(data->args[0]);
	if (data->args[1])
		free(data->args[1]);
	free(data->args);
	data->args = NULL;
	return 1;
}

int	use_cd(t_data *data)
{
	data->pwd_old = ft_calloc(1, MAXPATHLEN);
	data->pwd_cur = ft_calloc(1, MAXPATHLEN);
	getcwd(data->pwd_old, MAXPATHLEN);
	puts(data->pwd_old);
	if (data->args[1] == NULL)
		ft_home_cd(data);
	else
	{
		if (chdir(data->args[1]) == -1)
			puts("WRONG PUT");
		getcwd(data->pwd_cur, MAXPATHLEN);
		puts(data->pwd_cur);
	}
	return 1;
}

int main (int ac, char **av, char **env)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(*data));
	fill_env_path(data, env);
	data->args = malloc(sizeof(char **) * 100);
	while (av[i + 1])
	{
		data->args[i] = ft_strdup(av[i + 1]);
		i++;
	}
	use_cd(data);
	// ft_get_env(data);
	// ft_get_pwd(data);
}