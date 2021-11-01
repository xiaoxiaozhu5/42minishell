#include "ft_minishell.h"

int	ft_find_command(t_node *new_node, char *input, int *start, int *end)
{
	int k;
	int	is_alpha_begins;

	k = *start;
	is_alpha_begins = 0;
	while (k <= *end)
	{
		if (input[k] == STRING_QUOTE)
			new_node->command = ft_string_quote(input, &k);
		else if (is_alpha_begins && (!input[k] || input[k] == ' '|| input[k] == '\t' || input[k] == '|'))
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
	int k;
	int l;

	k = *start;
	while (k <= *end)
	{
		if (input[k] == '-' && input[k + 1])
		{
			if (!(input[k + 1] == ' ' || input[k + 1] == '\t'))
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

void	ft_build_cmd(t_node **list, char *input, int *start, int *end)
{
	t_node	*new_node;

	new_node = ft_list_create_back((void**)list, ft_node_create());
	*start = ft_find_command(new_node, input, start, end);
	*start = ft_find_flags(new_node, input, start, end);
//	if (!ft_next_redir(input, *start, *end))
//		*start = ft_find_args(new_node, input, start, end);
//	*start = ft_find_redirs(new_node, input, start, end);
//	*start = ft_str_find_alnum(input, *end + 1);
	*start = *end + 2;
	new_node->c_end = input[*end];
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
			ft_build_cmd(&cmds, input, &j, &i);
		i++;
	}
	env->cmds = &cmds;
	if (DEBUG_MODE == 1)
		ft_list_print(env->cmds);
}
