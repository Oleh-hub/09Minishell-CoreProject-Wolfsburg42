/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:11:51 by oruban            #+#    #+#             */
/*   Updated: 2024/06/21 10:12:10 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 06021 bonus part - &&
 */
/* int	execute_and(t_data *data, t_tree *tree)
{
	if (evaluate_execution(data, tree->left))
	{
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	if (evaluate_execution(data, tree->right))
	{
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	return (0);
} */

/* 
	roi 06021 bonus part - &&
 */
/* int	execute_or(t_data *data, t_tree *tree)
{
	if (evaluate_execution(data, tree->left))
	{
		if (evaluate_execution(data, tree->right))
		{
			data->exit_status = 1;
			return (1);
		}
		data->exit_status = 0;
		return (0);
	}
	data->exit_status = 0;
	return (data->exit_status);
}
 */