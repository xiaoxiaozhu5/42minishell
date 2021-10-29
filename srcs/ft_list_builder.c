#include "ft_minishell.h"

int	ft_issplit(const char *input, int i)
{
	if (input[i] == '|' || input[i] == '\0')
		return (1);
	return (0);
}

int	ft_args_end(const char *input, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		if ((input[i] == ' ' || input[i] == '\t') && (input[i + 1] == '>'
			|| input[i + 1] == '<'))
			return (i);
		i++;
	}
	return (i);
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
		}
		if (!onFlag && str[i] == '-' && (str[i + 1] && str[i + 1] != ' '
			&& str[i + 1] != '\t'))
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
	int	l;

	k = *start;
	while (k < *end)
	{
		if (input[k] && input[k] != ' ' && input[k] != '\t')
		{
			l = ft_args_end(input, *start, *end);
			new_node->args = ft_substr(input, k, l - k);
			printf("args start: %d, args len: %d\n", k, l - k);
			return (*end);
		}
		k++;
	}
	return (*start);
}

void	ft_add_redir(t_redir **list, char *input, int *k, int *end)
{
	t_redir	*new_node;
	int		type;
	char	*value;

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
	{
		(*k)++;
	}
	value = ft_substr(input, *k, *end - *k + 1);
	new_node->type = type;
	new_node->value = value;
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
		{
			printf("EST REDIR\n");
			ft_add_redir((t_redir **)&(new_node->redirs), input, &k, end);
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
	*start = ft_find_redirs(new_node, input, start, end);
	*start = ft_str_find_alnum(input, *end + 1);
	new_node->c_end = input[*end];
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
