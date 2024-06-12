/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:57:41 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 13:45:27 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_asterisks(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] != '*')
			return (0);
	}
	return (1);
}
