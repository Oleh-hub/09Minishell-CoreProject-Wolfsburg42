/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:16:05 by oruban            #+#    #+#             */
/*   Updated: 2024/06/04 11:16:32 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_logic_root(t_tree *tree)
{
	// printf ("&& or || in command line\n"); // roi tracing
	return (tree->type == T_AND || tree->type == T_OR);
}
