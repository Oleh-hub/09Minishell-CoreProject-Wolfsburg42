/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:41:24 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 09:13:01 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*replacing a '<<' sequence in the 'input_line' with the file name
from the current 'heredoc_file'.*/
void	copy_filename(t_data *data, t_copy_params *params)
{
	int	k;

	k = 0;
	*params->i += 2;
	if (data->input_line[*params->i] == ' ')
		(*params->new_input_line)[(*params->j)++] = \
		data->input_line[(*params->i)++];
	while ((*params->current_file)->filename[k])
	{
		(*params->new_input_line)[(*params->j)++] = \
		(*params->current_file)->filename[k++];
	}
	*params->current_file = (*params->current_file)->next;
}

/*function processes the original input line, detects heredoc sequences (<<),
and replaces them with corresponding filenames from a list of heredoc files,
constructing a new input line in the process. The helper function copy_filename
facilitates this replacement.*/
void	update_input_line(t_data *data)
{
	t_heredoc_file	*current_file;
	char			*new_input_line;
	int				i;
	int				j;
	t_copy_params	params;

	current_file = data->heredoc_file;
	i = 0;
	j = 0;
	if (!current_file)
		return ;
	new_input_line = ft_calloc(ft_strlen(data->input_line) + 10, sizeof(char));
	params.new_input_line = &new_input_line;
	params.i = &i;
	params.j = &j;
	params.current_file = &current_file;
	while (data->input_line[i])
	{
		if (data->input_line[i] == '<' && data->input_line[i + 1] == '<')
			copy_filename(data, &params);
		else
			new_input_line[j++] = data->input_line[i++];
	}
	ft_memdel(&data->input_line);
	data->input_line = new_input_line;
}
