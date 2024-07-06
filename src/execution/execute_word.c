/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:02:37 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 11:33:11 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  roi 0608
	executes the first word of the command:runs either a builtin or command 
	execution in minishell
	step by step description:
	- checking with is_builtin() if the command is a builtin or not
	 - and execute either builtin with execute_builitin() 
	- or command with execute_command()
 */
//************* checking the command line 0609 roi
//  out_t_tree("inside execute_word- BUILDIN / COMMAND execution choice", tree);
int	execute_word(t_data *data, t_tree *tree, int fd_inp, int fd_out)
{
	if (tree == NULL || tree->value == NULL || tree->args_array == NULL)
		return (1);
	if (is_builtin(tree->args_array[0]))
	{
		if (execute_builtin(data, tree, fd_out))
			return (data->exit_status);
	}
	else
	{
		if (ft_strlen(tree->value) == 0)
			return (1);
		if (execute_command(data, tree, fd_inp, fd_out))
			return (1);
	}
	return (0);
}

/* 
	roi 0621
	executing the external shell command 
 */
int	execute_command(t_data *data, t_tree *tree, int fd_inp, int fd_out)
{
	char			*exec_path;
	t_command_args	args;

	exec_path = find_executable_path(data, tree->args_array[0]);
	if (exec_path == NULL)
	{
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(tree->args_array[0], 0);
		ft_putstr_fd(": command not found\n", 0);
		data->exit_status = 127;
		return (1);
	}
	args.data = data;
	args.tree = tree;
	args.exec_path = exec_path;
	args.fd_inp = fd_inp;
	args.fd_out = fd_out;
	return (fork_command(&args));
}

/* 
	roi 0623
	the function is filling the envp array with the environment variables
  */
static void	fill_envp(char **envp, t_envir **lst)
{
	int		i;
	int		len;
	t_envir	*tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		len = ft_strlen(tmp->var_name) + ft_strlen(tmp->var_value) + 2;
		envp[i] = malloc(len);
		ft_strcpy(envp[i], tmp->var_name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], tmp->var_value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
}

/* 
	roi 0623
	the funciton is confverting the enviroment variables for the command 
	execution from the list format: "t_tnvir **lst" into 'char **envp' and 
	returns envp
	1 stage: allocate memory for the array of stings: envp
	2. colling the function fill_envp() to fill the envp array with the 
	environment variables 
 */
char	**env(t_envir **lst)
{
	char	**envp;
	t_envir	*tmp;
	int		i;

	if (!lst)
		return (NULL);
	i = 0;
	tmp = *lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	fill_envp(envp, lst);
	return (envp);
}

/* 
	roi 0623
	debugging fu
 */
/* void	print2darray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
 */