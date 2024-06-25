/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:00:44 by oruban            #+#    #+#             */
/*   Updated: 2024/06/21 11:58:02 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* roi 0605
 */

int	execute(t_data *data)
{
	/* int	result;

	result = evaluate_execution(data, data->tree);
	data->exit_status = result;
	return (result); */
	// out_t_data_data("!====tracning in execute()", data); //roi0605
	return (data->exit_status = evaluate_execution(data, data->tree));
}

/*  roi 0608
 */
int	execute_and_handle_files(t_data *data, t_tree *tree)
{
	int	fd_out;
	int	fd_inp;

	fd_out = get_output_file(tree);
	fd_inp = get_input_file(tree);
	if (fd_inp == -1)
	{
		if (fd_out != 1)
			close(fd_out);
		return (1);
	}
	if (execute_word(data, tree, fd_inp, fd_out))
	{
		if (fd_inp != 0)
			close(fd_inp);
		if (fd_out != 1)
			close(fd_out);
		return (data->exit_status);
	}
	if (fd_inp != 0)
		close(fd_inp);
	if (fd_out != 1)
		close(fd_out);
	return (0);
}

/* 
roi  0608-21
 */
int	evaluate_execution(t_data *data, t_tree *tree)
{
	int	result;

	/* if (is_logic_root(tree)) //  || and && handling
		if (execute_logic(data, tree))
			return (1); */
	// printf("\n(t_token_type) data->token_list->type = %d\n", data->token_list->type); // debug 0621
	// printf("\n(t_token_type) tree->type = %d\n", tree->type); // debug 0621
	if (tree->type == T_PIPE)
		if (execute_pipe(data, tree))
			return (1);
	if (is_word_root(tree))
	{
		result = execute_and_handle_files(data, tree); //roi0608 root is not needed
		return (result);
	}
	return (0);
}

/* 
	roi 0621
	|| and && handling
 */
/* int	execute_logic(t_data *data, t_tree *tree)
{
	if (tree->type == T_AND)
		if (execute_and(data, tree))
			return (1);
	if (tree->type == T_OR)
		if (execute_or(data, tree))
			return (1);
	return (0);
} */
