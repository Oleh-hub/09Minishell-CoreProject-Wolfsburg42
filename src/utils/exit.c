/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:57:21 by beredzhe          #+#    #+#             */
/*   Updated: 2024/07/03 19:15:42 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi0610
	frees all data allocation, prints error is any and exits with exit_code -
	free_data() is	freeing up all data allocation including one that are not
	freed by exit(), like list (data->env_list, etc)
	- outputs error message to STDERR_FILENO
	- exits with exit_code
 */

void	exit_shell(char *message, int exit_code, t_data *data)
{
	free_data(data);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(exit_code);
}
