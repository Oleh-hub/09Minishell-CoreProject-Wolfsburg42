/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:37:37 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 11:36:44 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0621 
	|| and && hanlding
 */

int	is_word_root(t_tree *tree)
{
	return (tree->type == T_WORD);
}

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
