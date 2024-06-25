/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:00:44 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 07:27:56 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* roi 0605
 */

int	execute(t_data *data)
{
	return (data->exit_status = evaluate_execution(data, data->tree));
}

