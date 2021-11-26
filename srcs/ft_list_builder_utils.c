#include "ft_minishell.h"

int	ft_find_flags_length(const char *str, int i)
{
	int	k;
	int	result;
	int	on_flag;

	k = 1;
	result = 0;
	on_flag = 1;
	while (str[i - 1] != '\0')
	{
		if (on_flag && (str[i] == ' ' || str[i] == '\t' || str[i] == '\0'
				|| str[i] == '|'))
		{
			on_flag = 0;
			result = k - 1;
		}
		if (!on_flag && str[i] == '-' && (str[i + 1] && str[i + 1] != ' '
				&& str[i + 1] != '\t'))
			on_flag = 1;
		if (!on_flag && str[i] != '-' && str[i] != ' ' && str[i] != '\t')
			return (result);
		k++;
		i++;
	}
	return (result);
}

int	ft_next_redir(const char *input, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '<' || input[i] == '>')
			return (i);
		else
			return (0);
	}
	while (i <= end)
	{
		if (input[i] == '<' || input[i] == '>')
			return (i);
		else if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (0);
}





int	ft_args_end(const char *input, int start, int end)
{
	int	i;
	int	in_qts;

	i = start;
	in_qts = 0;
	while (i <= end)
	{
		if (input[i] == STRING_QUOTE)
			in_qts = !in_qts;
		if (!in_qts)
		{
			if ((input[i] == '>' || input[i] == '<')
				|| ((input[i] == ' ' || input[i] == '\t')
					&& (ft_next_word_starts_with(input, "><|\0", i))))
			{
				return (i);
			}
		}
		i++;
	}
	return (i);
}
