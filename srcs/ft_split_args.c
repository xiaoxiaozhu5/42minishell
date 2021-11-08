#include "ft_minishell.h"

static int	ft_next_empty(const char *str, int start)
{
	int	i;
	int	in_qts;

	in_qts = 0;
	i = start + 1;
	while (str[i] && ((str[i] != ' ' && str[i] != '\t') || in_qts))
	{
		if (str[i] == STRING_QUOTE)
			in_qts = !in_qts;
		i++;
	}
	return (i);
}

static int	ft_next_quote(const char *str, int start)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != STRING_QUOTE)
		i++;
	return (i);
}

static int	ft_nbr_args(const char *args)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i] != '\0' && (size_t) i < ft_strlen(args) - 1)
	{
		if (args[i] == STRING_QUOTE)
		{
			j++;
			i += ft_next_quote(args, i) - i;
		}
		if (args[i] != ' ' && args[i] != '\t' && args[i] != STRING_QUOTE)
		{
			j++;
			i += ft_next_empty(args, i) - i - 1;
		}
		i++;
	}
	return (j);
}

static char	*ft_substr_q(char const *s, unsigned int start, size_t len)
{
	char	*result;
	char	*qt;
	result = ft_substr(s, start, len);
	qt = ft_strchr(result, STRING_QUOTE);
	while (qt)
	{
		ft_strpclear(result, qt);
		qt = ft_strchr(result, STRING_QUOTE);
	}
	return (result);
}

char	**ft_split_args(char const *args)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	strs = malloc(sizeof(char *) * (ft_nbr_args(args) + 1));
	if (!strs)
		return (0);
	while (args[i] != '\0' && (size_t) i < ft_strlen(args) - 1)
	{
		if (args[i] == STRING_QUOTE)
		{
			strs[j++] = ft_substr_q(args, i, ft_next_quote(args, i) - i + 1);
			i += ft_next_quote(args, i) - i;
		}
		if (args[i] != ' ' && args[i] != '\t' && args[i] != STRING_QUOTE)
		{
			strs[j++] = ft_substr_q(args, i, ft_next_empty(args, i) - i);
			i += ft_next_empty(args, i) - i - 1;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}
