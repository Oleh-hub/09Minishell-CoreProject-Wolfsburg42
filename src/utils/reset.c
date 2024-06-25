/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:04:10 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 10:14:12 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_data(t_data *data)
{
	data->s_quote = 0;
	data->d_quote = 0;
	data->forked = 0;
	if (data->root_directory && *data->root_directory)
		free_2darray(data->root_directory);
	if (data->heredoc_file)
	{
		free_heredoc_files(data->heredoc_file);
		data->heredoc_file = NULL;
	}
	data->root_directory = get_root_directory();
	if (data->input_line && ft_strlen(data->input_line) > 0)
		ft_memdel(&data->input_line);
	if (data->tree)
	{
		free_tree(&data->tree);
		data->tree = NULL;
	}
	if (data->token_list)
		free_tokens(&data->token_list, free);
}
