#include "../includes/ft_minishell.h"

char	*ft_echo(t_data *data)
{
	int i;
	int	arg_cnt;
	int	n_checker;
	int	echo_flag;

	n_checker = 1;
	i = 0;
	echo_flag = 0;
	if (ft_cmp(data->cmd, "echo") != 0)
	{
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putendl_fd(data->cmd, 1);
	}
	else
	{
		i = 1;
		while (data->args[i][0] == '-' && n_checker == 1)
		{
			arg_cnt = 1;
			while (data->args[i][arg_cnt] == 'n' 
				&& data->args[i][arg_cnt])
			{
				if (data->args[i][arg_cnt] != 'n')
				{
					n_checker = 0;
					break;
				} 
				arg_cnt++;
				if (!data->args[i][arg_cnt])
					echo_flag = 1;
			}
			i++;
		}
		while (data->args[i] != NULL)
		{
			ft_putstr_fd(data->args[i], data->fd);
			i++;
		}
	}
	return (NULL);
}
//need to do some tests;;;
