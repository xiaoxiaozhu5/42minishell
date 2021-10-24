#include "ft_minishell.h"

int	ft_issplit(const char *input, int i)
{
	if (input[i] == '|' || input[i] == '\0')
		return (1);
	return (0);
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
			return (1);
		else
			return (0);
	}
	while (i <= end)
	{
		if (input[i] == '<' || input[i] == '>')
			return (1);
		else if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (0);
}

int	ft_find_flags_length(const char *str, int i)
{
	int	k;
	int result;
	int	onFlag;

	k = 1;
	result = 0;
	onFlag = 1;
	while (str[i - 1] != '\0')
	{
		if (onFlag && (str[i] == ' ' || str[i] == '\t' || str[i] == '\0'))
		{
			onFlag = 0;
			result = k - 1;
			printf("result: %d;\n", result);
		}
		if (!onFlag && str[i] == '-' && (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\t'))
			onFlag = 1;
		if (!onFlag && str[i] != '-' && str[i] != ' ' && str[i] != '\t')
			return (result);
		k++;
		i++;
	}
	return (result);
}

int	ft_find_command(t_node *new_node, char *input, int *start, int *end)
{
	int k;

	k = *start;
	while (k <= *end)
	{
		if (!input[k] || input[k] == ' ')
		{
			new_node->command = ft_substr(input, *start, k - *start + 1);
			return (k);
		}
		k++;
	}
	return (*start);
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
				printf("Flags start: %d; Flags length: %d\n", k, l);
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
	int k;

	k = *start;
	while (k <= *end)
	{
		if (!input[k] || input[k] == ' ')
		{
			new_node->args = ft_substr(input, *start, k - *start + 1);
			return (k);
		}
		k++;
	}
	return (*start);
}

void	ft_build_cmd(t_node **list, char *input, int *start, int *end)
{
	t_node	*new_node;

	new_node = ft_list_create_back((void**)list, ft_node_create());
	*start = ft_str_find_alnum(input, *start);
	*start = ft_find_command(new_node, input, start, end);
	*start = ft_find_flags(new_node, input, start, end);
	if (!ft_next_redir(input, *start, *end))
		*start = ft_find_args(new_node, input, start, end);
	*start = ft_str_find_alnum(input, *end + 1);
}

void	ft_build_cmds(t_env *env, char *input)
{
	int		i;
	int		j;
	t_node	*cmds;

	i = 0;
	j = 0;
	cmds = 0;
	while (i - 1 < 0 || input[i - 1] != '\0')
	{
		if (ft_issplit(input, i))
			ft_build_cmd(&cmds, input, &j, &i);
		i++;
	}
	env->cmds = &cmds;
	ft_list_print(env->cmds);
}
