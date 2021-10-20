#include "../includes/ft_minishell.h"

char	*ft_echo(t_data *data)
{
	int i;

	i = 0;
	if (ft_cmp(data->cmd, "echo") != 0)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putendl_fd(data->cmd, 1);
	}
	else
	{
		if (data->redirr_type == NULL && data->pipe == 0)
			ft_putendl_fd(data->str, 1);
		else
		{
			data->str = ft_strjoin(data->str, "\n");
			return (data->str);
		}
	}
	return (NULL);
}
