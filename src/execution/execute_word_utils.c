/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:46:39 by oruban            #+#    #+#             */
/*   Updated: 2024/06/23 20:30:50 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	create_child_process(char **exec_path)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_strdel(exec_path);
	}
	return (pid);
}

void	redirect_fds(int fd_inp, int fd_out)
{
	if (fd_inp != STDIN_FILENO)
	{
		dup2(fd_inp, STDIN_FILENO);
		if (fd_inp != 0)
			close(fd_inp);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		if (fd_out != 1)
			close(fd_out);
	}
}

/*
	roi	0621
	executing execve() system call in child process because execve() 
	replaces the current process with a new process and therefore 
	STOPS executing the current	(reason why we have to do fork() twice 
	to implement '|')
	// Tracing:
	// printf("exec_path1: %s\n", exec_path); // roi 0621
 */

void	execute_forked_command(t_data *data, t_tree *tree, char *exec_path)
{
	char	**envp;

	envp = env(&data->env_list);
	// char **tmp = envp;
	// out_t_tree("inside execute_forked_command \n", tree);	// roi 0623
	// printf("exec_path: %s\n", exec_path); 					// roi 0623
	// while (tmp && *tmp) 									// roi 0623
	// {
	// 	printf("envp: %s\n", *tmp);
	// 	tmp++;
	// }
	if (execve(exec_path, tree->args_array, envp) == -1)
	{
		printf("execve failed\n");
		ft_strdel(&exec_path);
		data->exit_status = 127;
		exit(127);
	}
}

int	handle_exit_status(t_data *data, pid_t pid, int status, char **exec_path)
{
	if (g_child_pid == pid + 1)
		return (data->exit_status = 130, g_child_pid = 0, \
		ft_strdel(exec_path), 1);
	else if (g_child_pid == pid + 2)
		return (data->exit_status = 131, g_child_pid = 0, \
		ft_strdel(exec_path), 1);
	if (WIFEXITED(status))
		return (data->exit_status = WEXITSTATUS(status), \
		g_child_pid = 0, ft_strdel(exec_path), 1);
	return (g_child_pid = 0, ft_strdel(exec_path), 0);
}

int	fork_command(t_command_args *args)
{
	pid_t	pid;
	int		status;

	pid = create_child_process(&args->exec_path);
	if (pid == 0)
	{
		redirect_fds(args->fd_inp, args->fd_out);
		execute_forked_command(args->data, args->tree, args->exec_path);
	}
	else
	{
		g_child_pid = pid;
		waitpid(pid, &status, 0);
		return (handle_exit_status(args->data, pid, status, &args->exec_path));
	}
	return (0);
}
