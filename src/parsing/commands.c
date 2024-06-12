/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:37:13 by oruban            #+#    #+#             */
/*   Updated: 2024/06/08 18:50:56 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* roi 0607
looks through the list t_envir
 */
t_envir	*find_envir_variable(t_data *data, char *var_name, int len)
{
	t_envir	*current;

	// out_t_data_data("inside find_envir_variable()", data);
	out_t_envir("inside find_envir_variable()", data->env_list);
	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->var_name, var_name, len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
