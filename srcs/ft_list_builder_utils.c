/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_builder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricky <kricky@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:25:00 by kricky            #+#    #+#             */
/*   Updated: 2021/11/27 14:53:00 by kricky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_redir_value(char *input, int *k, int end)
{
	char	*value;
	int		start;
	int		in_qts;

	start = *k;
	in_qts = 0;
	if (input[start] == STRING_QUOTE)
		in_qts = !in_qts;
	while (*k <= end && ((input[*k] && input[*k] != ' '
				&& input[*k] != '\t' && input[*k] != '>'
				&& input[*k] != '<' && input[*k] != '|') || in_qts))
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

t_redir	*ft_add_redir(char *input, int *k, const int *end)
{
	t_redir	*new_redir;
	int		type;

	new_redir = ft_node_redir_create();
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
	new_redir->type = type;
	new_redir->value = ft_redir_value(input, k, *end);
	return (new_redir);
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
