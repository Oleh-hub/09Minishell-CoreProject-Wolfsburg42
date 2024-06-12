/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:34:40 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 13:42:38 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2darray(char **array)
{
	int i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		ft_memdel(&array[i]);
	free(array);
	array = NULL;
}
