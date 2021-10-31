#include "ft_minishell.h"

int	ft_check_next(const char *input, int i, char c)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	ft_check_single(const char *input, char quote, char in)
{
	int	i;
	int	counter;
	int	in_qts;

	i = 0;
	counter = 0;
	in_qts = 0;
	while (input[i] != '\0')
	{
		if (input[i] == in && (ft_check_next(input, i, in) || in_qts))
			in_qts = !in_qts;
		if (input[i] == quote && (i == 0 || input[i - 1] != '\\') && !in_qts)
			counter++;
		i++;
	}
	if (counter % 2 != 0)
		return (quote);
	return (0);
}

char	ft_check_start(const char *input, char c)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
	{
		i++;
	}
	if (input[i] == c)
		return (c);
	return (0);
}

char	ft_bad_usage(const char *input, char c)
{
	int	i;
	int	j;
	int	is_bad;

	i = 0;
	is_bad = 0;
	while (input[i] != '\0')
	{
		if (input[i] == c)
		{
			j = i;
			is_bad = 1;
			while (input[++j] != '\0')
			{
				if (input[j] != ' ' && input[j] != '\t' && input[j] != '|')
					is_bad = 0;
				if (is_bad && input[j] == '|')
					break ;
			}
			if (is_bad)
				return (c);
		}
		i++;
	}
	return (0);
}

int	ft_preparser(char *input)
{
	int	error;

	error = 0;
	error |= ft_error_unexpected_token(ft_check_single(input, '\'', '\"'));
	error |= ft_error_unexpected_token(ft_check_single(input, '\"', '\''));
	error |= ft_error_unexpected_token(ft_check_start(input, '|'));
	error |= ft_error_unexpected_token(ft_bad_usage(input, '|'));
	return (error);
}
