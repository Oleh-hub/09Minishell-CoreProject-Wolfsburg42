/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_delim_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:55:12 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 20:19:33 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_heredoc_file(t_data *data, char *filename, int id)
{
	t_heredoc_file	*new_file;

	new_file = malloc(sizeof(t_heredoc_file));
	new_file->filename = ft_strdup(filename);
	new_file->id = id;
	new_file->next = data->heredoc_file;
	data->heredoc_file = new_file;
}

void	free_heredoc_info(t_heredoc_info *info)
{
	if (info->filename)
		ft_memdel(&info->filename); // instead of ft_strdel(&info->filename); roi 0625
	if (info->limiter)
		ft_memdel(&info->limiter);
	if (info->token)
		ft_memdel(&info->token);
}
