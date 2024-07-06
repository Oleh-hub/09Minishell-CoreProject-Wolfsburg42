/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:19:58 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 12:23:48 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0611-19
	the function making an outpt in env viralbe format into file descriptor
	it got as argument fd_out in format "VARIABLE=Value\n"
 */
void	print_env_node(t_envir *env_node, int fd_out)
{
	t_envir	*env;

	if (!env_node)
		return ;
	env = env_node;
	if (!env->visible)
	{
		ft_putstr_fd(env->var_name, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(env->var_value, fd_out);
		ft_putstr_fd("\n", fd_out);
	}
}

void	print_env_node_sorted(t_envir *env_node, int fd_out)
{
	t_envir	*env;

	if (!env_node)
		return ;
	env = env_node;
	ft_putstr_fd("declare -x ", fd_out);
	ft_putstr_fd(env->var_name, fd_out);
	if (env->var_value && ft_strlen(env->var_value) > 0)
	{
		ft_putstr_fd("=\"", fd_out);
		ft_putstr_fd(env->var_value, fd_out);
		ft_putstr_fd("\"\n", fd_out);
	}
	else
		ft_putstr_fd("\n", fd_out);
}

void	free_envir_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	env_array = NULL;
}
