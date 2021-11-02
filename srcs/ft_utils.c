#include "ft_minishell.h"

int	ft_next_word_starts_with(const char *str, const char *set, int s)
{
	int	i;

	i = s;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (ft_strchr(set, str[i]))
		return (1);
	return (0);
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
