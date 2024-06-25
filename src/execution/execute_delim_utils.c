/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_delim_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 10:55:12 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/22 12:21:35 by beredzhe         ###   ########.fr       */
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
		ft_memdel(&info->filename);
	if (info->limiter)
		ft_memdel(&info->limiter);
	if (info->token)
		ft_memdel(&info->token);
}
