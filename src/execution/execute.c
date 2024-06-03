/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:54:41 by oruban            #+#    #+#             */
/*   Updated: 2024/06/03 15:40:22 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/execute.h"
#include "minishell.h"
#include "execute.h"

int	execute(t_data *data)
{
    return (data->exit_status = 1);
    // return (data->exit_status = evaluate_execution(data, data->tree));
}
