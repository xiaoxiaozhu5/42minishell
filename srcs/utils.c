#include "../includes/ft_minishell.h"


int	ft_cmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (s1[i] == 0 && s2[i] != 0)
		return (1);
	return (0);
}