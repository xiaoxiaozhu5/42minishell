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
	printf("%s\n", ERROR_CMD_NOT_FOUND);
}

void	ft_error_identifier(const char *cmd_name, const char identifier)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("'%c': ", identifier);
	printf("%s\n", ERROR_IDENTIFIER);
}

void	ft_error_homeless(const char *cmd_name)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", cmd_name);
	printf("%s\n", ERROR_HOMELESS);
}

void	ft_strerror(const char *error_msg1, const char *error_msg2)
{
	printf("%s: ", SHELL_NAME);
	printf("%s: ", error_msg1);
	printf("%s\n", error_msg2);
}
