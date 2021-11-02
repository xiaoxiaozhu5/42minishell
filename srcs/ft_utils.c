#include "ft_minishell.h"

char	*ft_cut_quote(const char *str, int *i)
{
	char	*result;
	int		start;

	start = *i;
	(*i)++;
	if (!str || str[start] != STRING_QUOTE)
		return (0);
	while (str[*i] && str[*i] != STRING_QUOTE)
		(*i)++;
	result = ft_substr(str, start + 1, *i - start - 1);
	(*i)++;
	return (result);
}

char	*ft_string_quote(const char *str, int *i)
{
	char	*result;
	int		start;

	start = *i;
	(*i)++;
	if (!str || str[start] != STRING_QUOTE)
		return (0);
	while (str[*i] && str[*i] != STRING_QUOTE)
		(*i)++;
	result = ft_substr(str, start + 1, *i - start - 1);
	(*i)++;
	return (result);
}

int	ft_is_split(const char *input, int i)
{
	if (input[i] == '|' || input[i] == '\0')
		return (1);
	return (0);
}

void	ft_redirs_print(t_redir **lst)
{
	t_redir	*iter;

	if (lst && *lst != 0)
	{
		iter = *lst;
		while (iter != 0)
		{
			if (iter->type == REDIRECT_LEFT)
				printf("Р-рект левый - значение [%s]\n", iter->value);
			else if (iter->type == REDIRECT_RIGHT)
				printf("Р-рект правый - значение [%s]\n", iter->value);
			else if (iter->type == REDIRECT_DOUBLE_LEFT)
				printf("Р-рект двойной левый - значение [%s]\n", iter->value);
			else if (iter->type == REDIRECT_DOUBLE_RIGHT)
				printf("Р-рект двойной правый - значение [%s]\n", iter->value);
			iter = iter->next;
		}
	}
}

void	ft_list_print(t_node **lst)
{
	int		i;
	t_node	*iter;

	if (*lst != 0)
	{
		i = 1;
		iter = *lst;
		while (iter != 0)
		{
			printf("---- \033[0;32mКоманда #%d\033[0m ----\n", i);
			printf("Выполнить: [%s]\n", iter->command);
			printf("Флаги: [%s]\n", iter->flags);
			printf("Аргументы: [%s]\n", iter->args);
			printf("Оканчивается: [%c]\n", iter->c_end);
			printf("Редиректы:\n");
			ft_redirs_print((t_redir **) &(iter->redirs));
			printf("--------------------\n");
			i++;
			iter = iter->next;
		}
	}
}
