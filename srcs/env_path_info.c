#include "../includes/ft_minishell.h"


int	ft_beautiful_path(t_data *data)
{
	int		i;
	int		j;
	char	*temp_str;

	i = 0;
	j = 0;
	while(data->path[0][j] != '/')
		j++;
	temp_str = ft_strdup(data->path[0] + j);
	free(data->path[0]);
	data->path[0] = ft_strdup(temp_str);
	free(temp_str);
	while(data->path[i])
	{
		temp_str = ft_strjoin(data->path[i], "/");
		free(data->path[i]);
		data->path[i] = ft_strdup(temp_str);
		free(temp_str);
		i++;
	}
	return (1);
}

int	find_path(t_data *data)
{
	char	*temp_str;
	int		i;
	int		j;

	i = 0;
	while(data->env[i])
	{
		j = 0;
		while(data->env[i][j] != '=')
			j++;
		temp_str = malloc(sizeof(char) * j + 1);
		ft_strlcpy(temp_str, data->env[i], j + 1);
		if (ft_cmp("PATH", temp_str) == 0)
		{
			data->path = ft_split(data->env[i], ':');
			ft_beautiful_path(data);
			return (1);
		}
		free(temp_str);
		i++;
	}
	return (0);
}

int	fill_env_path(t_data *data, char **env)
{
	int	i;

	i = 0;
	while(env[i++] != NULL);
	
	data->env = (char **)malloc(sizeof(char *) * (i + 1));
	data->env[i] = NULL;

	if (!data->env)
	{	
		puts("Error malloc data->env");
		exit(1);
	}
	i = 0;
	while(env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
	find_path(data);
	return 0;
}