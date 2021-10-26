#include "ft_minishell.h"

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
			printf("-------------------- \033[0;32mКоманда #%d\033[0m --------------------\n", i);
			printf("Выполнить: %s\n", iter->command);
			printf("Флаги: %s\n", iter->flags);
			printf("Аргументы: %s\n", iter->args);
			printf("Оканчивается: %c\n", iter->c_end);
			printf("----------------------------------------------------\n");
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
	tmp3 = ft_strdup(input + (*i)-- + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	return (tmp);
}
