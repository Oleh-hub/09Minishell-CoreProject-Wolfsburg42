/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:51:45 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 11:07:43 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envir_value(t_envir *envir, char *new_value)
{
	ft_memdel(&envir->var_value);
	envir->var_value = new_value;
}

void	incr_shell_lvl(t_data *data)
{
	int		level;
	t_envir	*envir;

	if (!data->env_list)
		return ;
	envir = find_envir_variable(data, "SHLVL", ft_strlen("SHLVL"));
	if (envir->var_value)
	{
		level = ft_atoi(envir->var_value) + 1;
		if (level <= 999)
			update_envir_value(envir, ft_itoa(level));
		else if (level == 1000)
			update_envir_value(envir, ft_strdup(""));
		else
			update_envir_value(envir, ft_strdup("1"));
	}
}
