#include "ft_minishell.h"

char	*ft_get_key(const char *key_value)
{
	int		i;
	char	*result;

	i = 0;
	while (key_value[i] && key_value[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (key_value[i] && key_value[i] != '=')
	{
		result[i] = key_value[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_find_key(char **envp, const char *key_value)
{
	int		i;
	char	*envp_key;
	char	*key;

	i = 0;
	key = ft_get_key(key_value);
	while (envp[i])
	{
		envp_key = ft_get_key(envp[i]);
		if (ft_strcmp(envp_key, key) == 0)
		{
			free(key);
			free(envp_key);
			return (i);
		}
		else
		{
			free(envp_key);
			i++;
		}
	}
	free(key);
	return (0);
}

void	ft_envp_replace(char **old_address, const char *key_value)
{
	char	*new_kv;

	new_kv = ft_strdup(key_value);
	free(*old_address);
	*old_address = new_kv;
}

void	ft_envp_update(char ***envp, const char *key_value)
{
	char	**new_envp;

	new_envp = ft_strscopy_append(*envp, key_value, 1);
	ft_strsfree(*envp);
	*envp = new_envp;
}

void	ft_envp_add(char ***envp, const char *key_value)
{
	int	exists_index;

	exists_index = ft_find_key(*envp, key_value);
	if (exists_index)
		ft_envp_replace(*envp + exists_index, key_value);
	else
		ft_envp_update(envp, key_value);
}
