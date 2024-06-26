/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:37:37 by oruban            #+#    #+#             */
/*   Updated: 2024/06/26 15:30:38 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0621 
	|| and && hanlding
 */
/* int	is_logic_root(t_tree *tree)
{
	return (tree->type == T_AND || tree->type == T_OR);
} */

int	is_word_root(t_tree *tree)
{
	return (tree->type == T_WORD);
}

/* 
	roi 0621 is not used in minishell
 */
/* int	is_special_root(t_tree *tree)
{
	return (tree->type == T_REDIR_INPUT
		|| tree->type == T_REDIR_OUTPUT
		|| tree->type == T_APPEND || tree->type == T_DELIM
		|| tree->type == T_THREE_IN);
} */

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
