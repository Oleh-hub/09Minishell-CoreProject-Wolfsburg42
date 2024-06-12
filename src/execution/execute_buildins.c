/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:14:56 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 07:25:04 by oruban           ###   ########.fr       */
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
	if (!ft_strncmp(tree->args_array[0], "echo", 4))
		return (data->exit_status = check_echo(data, tree, fd_out));
	// cd done
	if (!ft_strcmp(tree->args_array[0], "cd"))
		return (data->exit_status = execute_cd(data, tree->args_array[1]));
	// pwd done
	if (!ft_strcmp(tree->args_array[0], "pwd"))
		return (data->exit_status = execute_pwd(data));
	if (!ft_strcmp(tree->args_array[0], "export"))
		return(data->exit_status = execute_export(data, tree, fd_out));
	if (!ft_strcmp(tree->args_array[0], "unset"))
		return(data->exit_status = execute_unset(data, tree));
	// env done
	if (!ft_strcmp(tree->args_array[0], "env"))
		execute_env(&data->env_list, fd_out);
	// exit done FREE_DATA() left 4 benan
	if (!ft_strcmp(tree->args_array[0], "exit"))
		execute_exit(data, tree);
	return (0);
}

