#include "../includes/ft_minishell.h"

// int	ft_get_env(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while(data->env[i + 1])
// 	{
// 		printf("%s\n",data->env[i++]);
// 	}
// 	return (1);
// }

// int	ft_get_pwd(t_data *data)
// {
// 	data->pwd_cur = ft_calloc(1, MAXPATHLEN);
// 	getcwd(data->pwd_cur, MAXPATHLEN);
// 	printf("%s\n", data->pwd_cur);
// 	return 1;
// }