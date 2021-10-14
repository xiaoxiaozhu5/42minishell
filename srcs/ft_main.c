#include "ft_minishell.h"

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("\033[0;34m42minishell\033[0m: ");
		add_history(input);
		printf("%s", input);
		printf("\n");
	}
}
