/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2024/06/12 07:26:29 by oruban           ###   ########.fr       */
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
int	execute_word(t_data *data, t_tree *tree, int fd_inp, int fd_out)
{
	if (tree == NULL || tree->value == NULL || tree->args_array == NULL)
		return (1);
//************* checking the command line 0609 roi
//  out_t_tree("inside execute_word- BUILDIN / COMMAND execution choice", tree);
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
