/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:54:41 by oruban            #+#    #+#             */
/*   Updated: 2024/06/04 21:02:13 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/execute.h"
#include "minishell.h"

// int	execute_logic(t_data *data, t_tree *tree)
int	execute_logic(t_tree *tree)
{
	if (tree->type == T_AND)
		// if (execute_and(data, tree))
			return (1);
	if (tree->type == T_OR)
		// if (execute_or(data, tree))
			return (1);
	return (0);
}

int	evaluate_execution(t_data *data, t_tree *tree)
{
	(void)data; 
    (void) tree;
    // int	result;

	// if (is_logic_root(tree))
	// 	if (execute_logic(data, tree))
	// 		return (1);

	// if (tree->type == T_PIPE) printf("PIPE\n"); // roi tracing
		// if (execute_pipe(data, tree))
		//	 return (1);
	// if (is_word_root(tree))
	// {
	// 	result = execute_and_handle_files(data, tree);
	// 	return (result);
	// }
	return (0);
}

int	execute(t_data *data)
{
	return (data->exit_status = evaluate_execution(data, data->tree));
}
