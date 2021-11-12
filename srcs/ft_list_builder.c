#include "ft_minishell.h"

int	ft_find_command(t_node *new_node, char *input, int *start, int *end)
{
	int	k;
	int	is_alpha_begins;
	int	in_qts;

	*start = ft_str_find_alnum(input, *start);
	k = *start;
	is_alpha_begins = 0;
	in_qts = 0;
	while (k <= *end)
	{
		if (input[k] == STRING_QUOTE)
		{
			ft_striclear(input, k--);
			in_qts = !in_qts;
		}
		else if (is_alpha_begins && !in_qts && (!input[k]
				|| input[k] == ' ' || input[k] == '\t' || input[k] == '|'))
			new_node->command = ft_substr(input, *start, k - *start);
		if (input[k] && input[k] != ' ' && input[k] != '\t')
			is_alpha_begins = 1;
		if (new_node->command)
			break ;
		k++;
	}
	return (k);
}

int	ft_find_flags(t_node *new_node, char *input, int *start, int *end)
{
	int	k;
	int	l;

	k = *start;
	while (k <= *end)
	{
		if (input[k] == '-' && input[k + 1])
		{
			if (!(input[k + 1] == ' ' || input[k + 1] == '\t'
					|| ft_str_find_in_word(input, '-', k + 1)))
			{
				l = ft_find_flags_length(input, k);
				new_node->flags = ft_substr(input, k, l);
				return (k + l);
			}
		}
		if (input[k] != ' ' && input[k] != '\t')
			break ;
		k++;
	}
	return (*start);
}

int	ft_find_args(t_node *new_node, char *input, int *start, int *end)
{
	int		k;
	int		l;
	char	*args_not_splitted;

	k = *start;
	while (k < *end)
	{
		if (input[k] && input[k] != ' ' && input[k] != '\t')
		{
			l = ft_args_end(input, *start, *end);
			args_not_splitted = ft_substr(input, k, l - k);
			new_node->args = ft_split_args(args_not_splitted);
			free(args_not_splitted);
			return (l);
		}
		k++;
	}
	return (*start);
}

int	ft_find_redirs(t_node *new_node, char *input, int *start, int *end)
{
	int		k;

	if (!ft_next_redir(input, *start, *end))
		return (*start);
	k = *start;
	printf("Start poiska: %d\n", k);
	while (k < *end)
	{
		if (input[k] && (input[k] != ' ' && input[k] != '\t')
			&& (input[k] == '<' || input[k] == '>'))
			ft_add_redir((t_redir **)&(new_node->redirs), input, &k, end);
		else
			k++;
	}
	return (*start);
}

t_node	*ft_build_cmd(char *input, int *start, int *end)
{
	t_node	*new_node;

	new_node = ft_node_create();
	*start = ft_find_command(new_node, input, start, end);
	*start = ft_find_flags(new_node, input, start, end);
	if (!ft_next_redir(input, *start, *end))
		*start = ft_find_args(new_node, input, start, end);
	*start = ft_find_redirs(new_node, input, start, end);
	*start = *end + 1;
	new_node->c_end = input[*end];
	if (!new_node->args)
	{
		new_node->args = malloc(sizeof(char *) * 2);
		new_node->args[1] = 0;
	}
	new_node->args[0] = ft_strdup(new_node->command);
	return (new_node);
}
