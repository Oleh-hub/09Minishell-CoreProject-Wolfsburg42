/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:00:44 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 11:41:27 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* roi 0605
 */
	/* int	result;

	result = evaluate_execution(data, data->tree);
	data->exit_status = result;
	return (result); */
	// out_t_data_data("!====tracning in execute()", data); //roi0605
int	execute(t_data *data)
{
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
roi  0608-21 - 0701
'minishell: syntax error near unexpected token `||''
output should be implemented in case of '||' token 
 */
	/* if (is_logic_root(tree)) //  || and && handling
		if (execute_logic(data, tree))
			return (1); */
	// printf("\n(t_token_type) data->token_list->type = %d\n", 	
	// // data->token_list->type); // debug 0621
	// printf("\n(t_token_	type) tree->type = %d\n", tree->type); // debug 0621
	// {printf ("\033[31m evaluate_execution\n"); 	// debug 0701 || mstk hndlng
	// tree_out(tree); 							// debug 0701
	// printf("\033[0m\n");						// debug 0701}
int	evaluate_execution(t_data *data, t_tree *tree)
{
	int	result;

	if (tree->type == T_OR || tree->type == T_AND)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", \
			tree->value);
		return (1);
	}
	if (tree->type == T_PIPE)
		if (execute_pipe(data, tree))
			return (1);
	if (is_word_root(tree))
	{
		result = execute_and_handle_files(data, tree);
		return (result);
	}
	return (0);
}
