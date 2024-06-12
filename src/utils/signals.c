/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:46:20 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:28:16 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*In summary, handle_d handles two special cases: 
when input is NULL and when input is an empty string. 
In the first case, it exits the shell. In the second case, 
it frees input and signals the caller to skip the current iteration of the loop. 
If input is a non-empty string, it signals the caller 
to proceed with the loop.*/
int	handle_d(t_data *data, char *input)
{
	if (input == NULL)
	{
		rl_on_new_line();
		rl_redisplay();
		exit_shell("exit", 0, data);
	}
	if (ft_strlen(input) == 0)
	{
		ft_memdel(&input);
		return (1);
	}
	return (0);
}
