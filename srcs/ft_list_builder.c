#include "ft_minishell.h"

void	ft_build_cmd(t_node **list, char *input, int *i)
{
	t_node	*new_node;

	(void)input;
	(void)i;
	new_node = ft_list_create_back(list);
	new_node->command = ft_strdup("Hello world!");
	printf("Sozdali node s adressom %p\n", new_node);
}

int	ft_issplit(char c)
{
	if (c == '|' || c == '\0')
		return (1);
	return (0);
}

void	ft_build_cmds(t_env *env, char *input)
{
	t_node	*cmds;
	int		i;

	i = 0;
	cmds = NULL;
	while (input[i + 1] != '\0')
	{
		if (ft_issplit(input[i]))
			ft_build_cmd(&cmds, input, &i);
		i++;
	}
	env->cmds = &cmds;
	printf("List nachalo %s\n", (*(env->cmds))->command);
}
