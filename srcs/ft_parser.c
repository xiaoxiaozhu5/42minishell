#include "ft_minishell.h"

char	*ft_dollar(char *input, t_env *env, char **envp, int *i)
{
	int		start;
	char	*key;
	char	*key_with_dollar;
	char	*value;

	start = *i;
	if (!(ft_isdigit(input[(*i) + 1]) || input[(*i) + 1] == '?'))
	{
		while (input[++(*i)])
		{
			if (!(input[*i] == '_' || ft_isalnum(input[*i])))
				break ;
		}
	}
	else
		return (ft_unusual_dollar(input, env, i));
	if (*i == start + 1)
		return (input);
	key = ft_substr(input, start + 1, *i - start - 1);
	value = ft_get_value(key, envp);
	free(key);
	key_with_dollar = ft_substr(input, start, *i - start);
	if (value)
		ft_str_replace_free(&input, key_with_dollar, value);
	return (input);
}

char	*ft_slash(char *input, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*result;

	tmp = ft_substr(input, 0, *i);
	tmp2 = ft_strdup(input + *i + 1);
	result = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free(input);
	++(*i);
	return (result);
}

char	*ft_quotes(char *input, int *i)
{
	int		start;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	start = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\'')
			break ;
	}
	tmp = ft_substr(input, 0, start);
	tmp2 = ft_substr(input, start + 1, *i - start - 1);
	tmp3 = ft_strdup(input + *i + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	free(input);
	(*i) = (*i) - 2;
	return (tmp);
}

char	*ft_double_quotes(char *input, t_env *env, char **envp, int *i)
{
	char	*result;
	int		j;
	int		index_dollar;
	int		rollback_index;

	j = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\\' && (input[*i + 1] == '\"'
				|| input[*i + 1] == '$' || input[*i + 1] == '\\'))
			input = ft_slash(input, i);
		if (input[*i] == '\"')
			break ;
	}
	result = ft_dq_util(input, j, i);
	rollback_index = *i;
	index_dollar = ft_str_find(input, '$', j, *i);
	if (index_dollar)
	{
		*i = index_dollar - 1;
		result = ft_dollar(input, env, envp, i);
		*i = rollback_index;
	}
	return (result);
}

char	*ft_parser(char *input, t_env *env, char **envp)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			input = ft_quotes(input, &i);
		if (input[i] == '\\')
			input = ft_slash(input, &i);
		if (input[i] == '\"')
			input = ft_double_quotes(input, env, envp, &i);
		if (input[i] == '$')
			input = ft_dollar(input, env, envp, &i);
		i++;
	}
	// В двойных ковычках работает доллар
	printf("Спарсилось как: [%s]\n", input);
	return (input);
}
