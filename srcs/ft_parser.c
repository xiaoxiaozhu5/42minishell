#include "ft_minishell.h"

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

t_env	*ft_parser(char *input)
{
	int		i;
	t_env	*env;

	i = 0;
	env = malloc(sizeof(t_env));
	while (input[i])
	{
		if (input[i] == '\'')
			input = ft_quotes(input, &i);
		if (input[i] == '\\')
			input = ft_slash(input, &i);
		if (input[i] == '\"')
			input = ft_double_quotes(input, &i);
		i++;
	}
	printf("Result parser: %s\n", input);
	return (env);
}
