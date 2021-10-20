#include "ft_minishell.h"

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
	free(input);
	return (tmp);
}
