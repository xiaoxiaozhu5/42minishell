#include "ft_minishell.h"

int	ft_check_right(const char *input, int i, char c)
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
		if (input[i] == in && (ft_check_right(input, i, in) || in_qts))
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
	int	in_qts;

	i = 0;
	in_qts = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\"' || input[i] == '\'')
			in_qts = !in_qts;
		if (input[i] == c && !in_qts)
			return (c);
		else if (input[i] == '\"' || input[i] == '\'')
			i++;
		else
			break ;
	}
	return (0);
}

char	ft_check_slash(const char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && (size_t) i + 1 >= ft_strlen(input)
				&& (i - 1 < 0 || input[i - 1] != '\\'))
			return ('\\');
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
	error |= ft_error_unexpected_token(ft_check_start(input, ';'));
	error |= ft_error_unexpected_token(ft_check_slash(input));
	return (error);
}
