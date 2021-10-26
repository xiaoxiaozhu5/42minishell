#include "../includes/ft_minishell.h"

int main(int ac, char **av, char **env)
{
	// char	*a;

	t_data	*data;
	data = malloc(sizeof(*data));
	fill_env_path(data, env);
	data->cmd = malloc(sizeof(char) * ft_strlen(av[1] + 1));
	data->str = malloc(sizeof(char) * ft_strlen(av[2] + 1));
	data->redirr_type = malloc(sizeof(char) * ft_strlen(av[3]));
	data->file_name = malloc(sizeof(char) * ft_strlen(av[4]));

	//************ будет в парсере
	data->flags = malloc(sizeof(char **));
	data->flags[0] = ft_strdup(data->cmd);
	data->flags[1] = NULL;
	//************ будет в парсере

	data->cmd = av[1];
	data->str = av[2];
	data->redirr_type = av[3];
	data->file_name = av[4];
	data->flag = NULL;
	data->fd = 1;
	if (data->redirr_type[0] != '|')
		ft_redir(NULL, data);
	else
		ft_pipe(data);
}