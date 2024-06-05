#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
	char *s;
	while (1)
	{
		s = readline ("minishell %");
		printf("Input: %s\n", s);
		free(s);
	}
}
