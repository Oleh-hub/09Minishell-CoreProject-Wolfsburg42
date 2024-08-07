/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:18:11 by oruban            #+#    #+#             */
/*   Updated: 2024/07/01 20:18:30 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *file_name, int flags)
{
	return (open(file_name, flags, 0644));
}

static void	update_last_fd(int *last_fd, int new_fd)
{
	if (new_fd >= 0)
	{
		if (*last_fd != 1)
			close(*last_fd);
		*last_fd = new_fd;
	}
}

int	get_output_file(t_tree *tree)
{
	int		fd;
	int		last_fd;
	char	*file_name;
	t_tree	*curr;

	curr = tree->right;
	last_fd = 1;
	while (curr && curr->type != T_NEWLINE)
	{
		file_name = ft_strdup(curr->value);
		if (curr->type == T_REDIR_OUTPUT)
		{
			fd = open_file(file_name, O_WRONLY | O_CREAT | O_TRUNC);
			update_last_fd(&last_fd, fd);
		}
		else if (curr->type == T_APPEND)
		{
			fd = open_file(file_name, O_WRONLY | O_CREAT | O_APPEND);
			update_last_fd(&last_fd, fd);
		}
		ft_memdel(&file_name);
		curr = curr->right;
	}
	return (last_fd);
}
