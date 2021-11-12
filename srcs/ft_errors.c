#include "ft_minishell.h"

int	ft_error_unexpected_token(const char token)
{
	if (token)
	{
		printf("%s: ", SHELL_NAME);
		printf("%s ", ERROR_UNEXPECTED_TOKEN);
		printf("`%c`\n", token);
	}
	return (token);
}

void	ft_error_cmd_fail(const char *cmd_name)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("%s\n", ERROR_CMD_FAIL);
}

void	ft_error_identifier(const char *cmd_name, const char identifier)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("'%c': ", identifier);
	printf("%s\n", ERROR_IDENTIFIER);
}
