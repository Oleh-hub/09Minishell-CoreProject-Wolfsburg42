
#include "minishell.h"

void	create_pipe_and_check(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		printf("minishell: pipe error\n");
		exit(-1);
	}
}

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
