#include "ft_minishell.h"

char	*ft_dollar(char *input, char **envp, int *i)
{
	int		start;
	char	*key;
	char	*key_with_dollar;
	char	*value;

	(void)envp;
	start = *i;
	while (input[++(*i)])
	{
		if (!(input[*i] == '_' || ft_isalnum(input[*i])))
			break ;
	}
	if (*i == start + 1)
		return (input);
	// TODO echo $USE segmentation fault
	key = ft_substr(input, start + 1, *i - start - 1);
	value = ft_get_value(key, envp);
	free(key);
	key_with_dollar = ft_substr(input, start, *i - start);
	ft_str_replace(&input, key_with_dollar, value);
	free(key_with_dollar);
	free(value);
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
	(*i) -= 1;
	return (tmp);
}

char	*ft_double_quotes(char *input, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\\' && (input[*i + 1] == '\"'
				|| input[*i + 1] == '$' || input[*i + 1] == '\\'))
			input = ft_slash(input, i);
		if (input[*i] == '\"')
			break ;
	}
	tmp = ft_substr(input, 0, j);
	tmp2 = ft_substr(input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(input + (*i)-- + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	free(input);
	return (tmp);
}

char	*ft_parser(char *input, char **envp)
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
			input = ft_double_quotes(input, &i);
		if (input[i] == '$')
			input = ft_dollar(input, envp, &i);
		i++;
	}
	printf("Спарсилось как: [%s]\n", input);
	return (input);
}
