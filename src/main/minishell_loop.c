/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:55:18 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/01 21:56:46 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_loop(t_data *data)
{
	char	*input;
	int		exit_status; // roi

	exit_status = EXIT_SUCCESS; // roi
	while (1)
	{
		/* 1.Here have to write function to reset */
		/*2.to avoid segmentation fault. Delete later*/
		if (data == NULL)
		{
			fprintf(stderr, "Error: data is NULL\n");
			exit(1);
		}
		if (data->input_minishell == NULL)
		{
			fprintf(stderr, "Error: data->input_minishell is NULL\n");
			exit(1);
		}
		input = readline(data->input_minishell);
		if (handle_d(data, input))
			continue;
		if (ft_strlen(input) > 0)
			add_history(input);
		if (has_unclosed_quotes(input))
			continue;
		data->input_line = trim_input(input);
		ft_memdel((void *)&input);
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue;
		// if ((special_chars(data->input_line)))
		// 	continue;
		printf("Input proccesed: %s\n", data->input_line); //working trim
		printf("Input: %s\n", input); //standart trim. I free it already
		{ // roi - executable part
			// if (!has_pipe(input)) 
			// if (!0) // no pipe
				exit_status = execute_one_command();
				// exit_status = execute_one_command(input, &minienv);
			// else
			// {
			// 	commands = split_commands(input);
			// 	free(input);
			// 	exit_status = execute_multiple_commands(commands, &minienv);
			// 	free_array(commands);
			// }
		}
		
		free(input);
	}
	{ // roi
		return (exit_status);
	}
}
