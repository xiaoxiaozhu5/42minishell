#include "ft_minishell.h"

void	ft_clear_redirs(t_redir **lst)
{
	t_redir	*iter;
	t_redir	*temp;

	temp = *lst;
	while (temp)
	{
		iter = temp->next;
		if (temp->value)
			free(temp->value);
		free(temp);
		temp = iter;
	}
	*lst = 0;
}

void	ft_clear_nodes(t_node **lst)
{
	t_node	*iter;
	t_node	*temp;

	temp = *lst;
	while (temp)
	{
		iter = temp->next;
		if (temp->redirs)
			ft_clear_redirs(temp->redirs);
		if (temp->command)
			free(temp->command);
		if (temp->flags)
			free(temp->flags);
		if (temp->args)
			free(temp->args);
		free(temp);
		temp = iter;
	}
	*lst = 0;
}

void	ft_clear_cmds(t_env *env)
{
	ft_clear_nodes(&env->cmds);
	env->cmds = 0;
}
