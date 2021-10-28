#include "ft_minishell.h"

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
			printf("Выполнить: %s\n", iter->command);
			printf("Флаги: %s\n", iter->flags);
			printf("Аргументы: %s\n", iter->args);
			printf("Оканчивается: %c\n", iter->c_end);
			printf("Редиректы:\n");
			ft_redirs_print((t_redir **) &(iter->redirs));
			printf("--------------------\n");
			i++;
			iter = iter->next;
		}
	}
}

char *ft_dq_util(char *input, int j, int *i)
{
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	tmp = ft_substr(input, 0, j);
	tmp2 = ft_substr(input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(input + *i + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	free(input);
	printf("Строка будет: [%s]\n", tmp);
	printf("i будет на: %d\n", *i);
	// " /Users/kricky/Desktop/minishell ";
	return (tmp);
}
