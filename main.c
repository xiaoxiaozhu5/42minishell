#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft/libft.h"

int main (int ac, char **av, char **env)
{
	char *str;
	char **splitted_str;

	// str = malloc(PATH_MAX);
	str = getenv("PATH");
	puts(str);
	splitted_str = ft_split(str, ':');
	puts(splitted_str[0]);
}