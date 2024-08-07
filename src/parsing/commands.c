/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:37:13 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 12:37:24 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths, char **original_paths)
{
	paths = original_paths;
	while (*paths)
	{
		ft_memdel(paths);
		paths++;
	}
	free(original_paths);
}

static char	*duplicate_cmd_and_free_paths(char *cmd, char **paths)
{
	char	*command;

	command = ft_strdup(cmd);
	free_2darray(paths);
	return (command);
}

static char	*free_paths_and_return_cmd(char **paths, char **orig_p, char *cmd)
{
	free_paths(paths, orig_p);
	return (cmd);
}

char	*find_executable_path(t_data *data, char *cmd)
{
	char	*tmp;
	char	*command;
	char	**paths;
	t_envir	*path;
	char	**original_paths;

	path = find_envir_variable(data, "PATH", 4);
	if (!path)
		return (NULL);
	paths = ft_split(path->var_value, ':');
	original_paths = paths;
	while (*paths)
	{
		if (access(cmd, X_OK) == 0)
			return (duplicate_cmd_and_free_paths(cmd, paths));
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		ft_memdel(&tmp);
		if (access(command, F_OK) == 0)
			return (free_paths_and_return_cmd(paths, original_paths, command));
		ft_memdel(&command);
		paths++;
	}
	free_paths(paths, original_paths);
	return (NULL);
}

/* roi 0607
looks through the list t_envir
 */
	// out_t_data_data("inside find_envir_variable()", data);
	// out_t_envir("inside find_envir_variable()", data->env_list);
t_envir	*find_envir_variable(t_data *data, char *var_name, int len)
{
	t_envir	*current;

	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->var_name, var_name, len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
