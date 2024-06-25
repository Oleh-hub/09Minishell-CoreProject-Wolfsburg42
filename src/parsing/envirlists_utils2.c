/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirlists_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:54:35 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 19:48:11 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envir	*ft_envnew(void)
{
	t_envir	*head;

	head = malloc(sizeof(t_envir));
	if (!head)
		return (NULL);
	head->var_name = NULL;
	head->var_value = NULL;
	head->visible = 0;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}
