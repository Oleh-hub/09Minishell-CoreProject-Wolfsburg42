/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:19:58 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 07:52:25 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0611
	the function making an outpt in env viralbe format into file descriptor
	it got as argument fd_out
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
