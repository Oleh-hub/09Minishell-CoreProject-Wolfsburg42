/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:01 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 10:51:11 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
	(void)envp;
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->env_list = NULL;
	(*data)->heredoc_file = NULL;
	(*data)->sorted_env_list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	(*data)->root_directory = NULL;
	(*data)->exit_status = 0;
	(*data)->input_minishell = "minishell>> ";
	(*data)->pid = getpid();
	(*data)->curr_dir = getcwd(NULL, 0);
	fill_env(envp, *data);
	incr_shell_lvl(*data);
}
