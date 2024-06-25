/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:04:09 by oruban            #+#    #+#             */
/*   Updated: 2024/06/21 15:05:04 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static pid_t	create_pipe_child(t_pipe_info *args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		close (args->pipe_fd[args->end]);
		dup2(args->pipe_fd[1 - args->end], args->std_fd);
		close(args->pipe_fd[1 - args->end]);
		if (evaluate_execution(args->data, args->tree) == -1)
			exit(127);
		exit(0);
	}
	return (pid);
} */
/* 
	roi 0621
	if child process 
 */
static pid_t	create_and_check_child(t_pipe_info *args)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		close (args->pipe_fd[args->end]);
		dup2(args->pipe_fd[1 - args->end], args->std_fd);
		close(args->pipe_fd[1 - args->end]);
		if (evaluate_execution(args->data, args->tree) == -1)
			exit(127);
		exit(0);
	}
	if (pid < 0)
	{
		printf("minishell: fork error\n");
		exit(-1);
	}
	return (pid);
}

/* 
	roi 0621
	waits for the child proccess pid, gives *status its value
	changes the value of teh global variable g_child_pid to 0
 */
static void	wait_for_child(pid_t pid, int *status)
{
	g_child_pid = pid;
	waitpid(pid, status, 0);
	g_child_pid = 0;
}

/* 
	roi 0621
	handling pipe '|' in command
	createtion of two child processes left and right from '|'
 */
int	execute_pipe(t_data *data, t_tree *tree)
{
	int				pipe_fd[2];
	pid_t			pid[2];
	int				status;
	t_pipe_info		args;

	create_pipe_and_check(pipe_fd);
	args.pipe_fd = pipe_fd;
	args.data = data;
	args.tree = tree->left;
	args.end = 0;
	args.std_fd = STDOUT_FILENO;
	pid[0] = create_and_check_child(&args);
	args.tree = tree->right;
	args.end = 1;
	args.std_fd = STDIN_FILENO;
	pid[1] = create_and_check_child(&args);
	close_pipe(pipe_fd);
	wait_for_child(pid[0], &status);
	wait_for_child(pid[1], &status);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	return (0);
}