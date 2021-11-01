#include "ft_minishell.h"

void	ft_str_replace_free(char **str, char *replace, char *insert, int *i)
{
	ft_str_replace(str, replace, insert, *i);
	free(replace);
	free(insert);
}

char	*ft_remove_clear_quotes(char *input, int start, int *end)
{
	int		i;
	int		is_clear;
	char	*result;

	i = start + 1;
	is_clear = 1;
	while (input[i] && i < *end)
	{
		if (input[i] == ' ' || input[i] == '\t' || input[i] == '|')
		{
			is_clear = 0;
			break ;
		}
		i++;
	}
	if (is_clear)
	{
		result = ft_striclear(input, start, *end);
		free(input);
		*end = *end - 2;
		return (result);
	}
	return (input);
}

char	*ft_dollar(char *input, t_env *env, int *i)
{
	int		start;
	char	*key;
	char	*key_with_dollar;
	char	*value;

	start = *i;
	if (ft_isdigit(input[(*i) + 1]) || input[(*i) + 1] == '?')
		return (ft_unusual_dollar(input, env, i));
	while (input[++(*i)])
	{
		if (!(input[*i] == '_' || ft_isalnum(input[*i])))
			break ;
	}
	if (*i == start + 1)
		return (input);
	key = ft_substr(input, start + 1, *i - start - 1);
	value = ft_get_value(key, env->envp);
	free(key);
	key_with_dollar = ft_substr(input, start, *i - start);
	if (value)
		ft_str_replace_free(&input, key_with_dollar, value, &start);
	return (input);
}

char*	ft_quotes(char *input, const char c, int *i)
{
	int		start;

	// Если нет пробелов или табов или пайпов просто убрать а не менять
	start = *i;
	input[start] = STRING_QUOTE;
	while (input[++(*i)])
	{
		if (input[*i] == c)
			break ;
	}
	input[*i] = STRING_QUOTE;
	input = ft_remove_clear_quotes(input, start, i);
	return (input);
}

char	*ft_parser(char *input, t_env *env)
{
	int		i;
	int		in_qts;
	int		in_d_qts;

	i = 0;
	in_qts = 0;
	in_d_qts = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			in_qts = !in_qts;
		else if (input[i] == '\"')
			in_d_qts = !in_d_qts;
		else if (input[i] == '$' && (!in_qts || in_d_qts))
			input = ft_dollar(input, env, &i);
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			input = ft_quotes(input, '\'', &i);
		else if (input[i] == '\"')
			input = ft_quotes(input, '\"', &i);
		i++;
	}
	return (input);
}
