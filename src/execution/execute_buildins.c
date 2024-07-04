/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:14:56 by oruban            #+#    #+#             */
/*   Updated: 2024/07/04 15:16:22 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0610 roi
checking if command 'cmd' is a buildin command or not
*/
int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/* roi 06010
if the command is a builtin like 'cd' or 'exi't- > execute_cd() 
and set data->exit_status
 */
int	execute_builtin(t_data *data, t_tree *tree, int fd_out)
{
	//echo, echo -n done
	if (!ft_strncmp(tree->args_array[0], "echo", 4))
		return (data->exit_status = check_echo(data, tree, fd_out));
	// cd done
	if (!ft_strcmp(tree->args_array[0], "cd"))
		return (data->exit_status = execute_cd(data, tree->args_array[1]));
	// pwd done
	if (!ft_strcmp(tree->args_array[0], "pwd"))
		return (data->exit_status = execute_pwd(data));
	if (!ft_strcmp(tree->args_array[0], "export"))
		return (data->exit_status = execute_export(data, tree, fd_out));
	// unset done
	if (!ft_strcmp(tree->args_array[0], "unset"))
		return (data->exit_status = execute_unset(data, tree));
	// env done
	if (!ft_strcmp(tree->args_array[0], "env"))
		execute_env(&data->env_list, fd_out);
	// exit done FREE_DATA() left 4 benan
	if (!ft_strcmp(tree->args_array[0], "exit"))
		execute_exit(data, tree);
	return (0);
}

/* 
roi 0612

if the command is 'echo' -> execute_echo() but if
when tree->args_array[0] may be longer than 4 and contain 'echo' like 'echoolll'
 - 'echolllllllllll: command not found' is printed out
I have to use ft_strncmp() because I am not sure that 
 */
int	check_echo(t_data *data, t_tree *tree, int fd_out)
{
	// tracing:
	// out_t_tree("check_echo()", tree); //
	// printf("\033[34m=====================\033[0m\n");//
	if (!ft_strcmp(tree->args_array[0], "echo"))
	{
		if (execute_echo(tree->args_array, fd_out))
			return (1);
	}
	else
	{
		if (!ft_strncmp(tree->args_array[0], "echo", 4))
		{
			ft_putstr_fd("minishell: ", fd_out);
			ft_putstr_fd(tree->args_array[0], fd_out);
			ft_putstr_fd(": command not found\n", fd_out);
			data->exit_status = 127;
			return (1);
		}
	}
	return (0);
}
