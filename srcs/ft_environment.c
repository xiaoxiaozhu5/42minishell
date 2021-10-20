#include "ft_minishell.h"

static int	checker(const char *key, char *skey)
{
	int	result;

	result = (skey && ft_strlen(key) == ft_strlen(skey)
			&& ft_strncmp(key, skey, ft_strlen(key)) == 0);
	free(skey);
	return (result);
}

char	*ft_digit_dollar(char *input, int *i)
{
	int		start;
	char	*begin;
	char	*end;
	char	*result;

	start = *i;
	while (input[++(*i)])
	{
		if (!ft_isdigit(input[*i]))
			break ;
	}
	begin = ft_substr(input, 0, start);
	end = ft_strdup(input + *i);
	result = ft_strjoin(begin, end);
	free(input);
	free(begin);
	free(end);
	return (result);
}

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
		if (checker(key, skey))
			svalue = ft_strdup(&envp[i][j + 1]);
		if (svalue)
			break ;
	}
	if (!svalue)
		svalue = ft_strdup("");
	return (svalue);
}
