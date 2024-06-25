/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_checkers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:45:42 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 21:40:55 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\\' || str[i] == ';') && !in_quotes(str, i))
		{
			printf("minishell: Not required to interpret `%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
