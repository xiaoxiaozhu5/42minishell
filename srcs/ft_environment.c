#include "ft_minishell.h"

char	*ft_get_value(const char *key, char **envp)
{
	int		i;
	int		j;
	char	*skey;
	char	*svalue;

	i = -1;
	svalue = 0;
	while (envp[++i])
	{
		skey = 0;
		j = 0;
		if (ft_strnstr(envp[i], key, ft_strlen(key)))
		{
			while (envp[i][j] != '=')
				j++;
			skey = ft_substr(envp[i], 0, j);
		}
		if (skey && ft_strlen(key) == ft_strlen(skey)
				&& ft_strncmp(key, skey, ft_strlen(key)) == 0)
			svalue = ft_strdup(&envp[i][j + 1]);
		free(skey);
		if (svalue)
			break ;
	}
	return (svalue);
}
