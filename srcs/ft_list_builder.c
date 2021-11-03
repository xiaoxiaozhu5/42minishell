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
			ft_striclear(input, k);
			k--;
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
			if (!(input[k + 1] == ' ' || input[k + 1] == '\t' ||
					ft_str_find_in_word(input, '-', k + 1)))
			{
				l = ft_find_flags_length(input , k);
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
	char	*qt;

	k = *start;
	while (k < *end)
	{
		if (input[k] && input[k] != ' ' && input[k] != '\t')
		{
			l = ft_args_end(input, *start, *end);
			new_node->args = ft_substr(input, k, l - k);
			qt = ft_strchr(new_node->args, STRING_QUOTE);
			while (qt)
			{
				ft_strpclear(new_node->args, qt);
				qt = ft_strchr(new_node->args, STRING_QUOTE);
				*end = *end - 1;
			}
			return (l);
		}
		k++;
	}
	return (*start);
}

char	*ft_redir_value(char *input, int *k, int end)
{
	char	*value;
	int		start;
	int		in_qts;

	start = *k;
	in_qts = 0;
	if (input[start] == STRING_QUOTE)
		in_qts = !in_qts;
	while (*k <= end && ((input[*k] != ' ' && input[*k] != '\t') || in_qts) && (input[*k] != '>' && input[*k] != '<'))
	{
		(*k)++;
		if (input[*k] == STRING_QUOTE)
			in_qts = !in_qts;
	}
	value = ft_substr(input, start, *k - start);
	while (ft_strchr(value, STRING_QUOTE))
		ft_strpclear(value, ft_strchr(value, STRING_QUOTE));
	return (value);
}

void	ft_add_redir(t_redir **list, char *input, int *k, int *end)
{
	t_redir	*new_node;
	int		type;

	new_node = ft_list_create_back((void**)list, ft_node_redir_create());
	if (input[*k] == '<' && input[*k + 1] == '<')
		type = REDIRECT_DOUBLE_LEFT;
	else if (input[*k] == '>' && input[*k + 1] == '>')
		type = REDIRECT_DOUBLE_RIGHT;
	else if (input[*k] == '<')
		type = REDIRECT_LEFT;
	else if (input[*k] == '>')
		type = REDIRECT_RIGHT;
	while (*k < *end && (input[*k] == ' ' || input[*k] == '\t'
						 || input[*k] == '<' || input[*k] == '>'))
		(*k)++;
	new_node->type = type;
	new_node->value = ft_redir_value(input ,k, *end);
}

int	ft_find_redirs(t_node *new_node, char *input, int *start, int *end)
{
	int		k;

	if (!ft_next_redir(input, *start, *end))
		return (*start);
	k = *start;
	while (k < *end)
	{
		if (input[k] && (input[k] != ' ' && input[k] != '\t') && (input[k] == '<' || input[k] == '>'))
			ft_add_redir((t_redir **)&(new_node->redirs), input, &k, end);
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
	return (new_node);
}

void	ft_build_cmds(t_env *env, char *input)
{
	int		i;
	int		j;
	t_node	*cmds;
	int		in_qts;

	i = 0;
	j = 0;
	cmds = 0;
	in_qts = 0;
	while (i - 1 < 0 || input[i - 1] != '\0')
	{
		if (input[i] == STRING_QUOTE)
			in_qts = !in_qts;
		if (!in_qts && ft_is_split(input, i))
			ft_list_create_back((void**)&cmds, ft_build_cmd(input, &j, &i));
		i++;
	}
	env->cmds = &cmds;
	if (DEBUG_MODE)
		ft_list_print(env->cmds);
}
