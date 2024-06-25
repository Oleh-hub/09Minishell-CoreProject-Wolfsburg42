/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_envir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:07:17 by oruban            #+#    #+#             */
/*   Updated: 2024/06/19 10:19:37 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0613
*/
t_envir	*copy_envir_list(t_envir *original)
{
	t_envir	*copy;
	t_envir	*node;
	t_envir	*prev;

	copy = NULL;
	node = NULL;
	prev = NULL;
	while (original)
	{
		node = ft_envnew();
		node->var_name = strdup(original->var_name);
		node->var_value = strdup(original->var_value);
		node->visible = original->visible;
		node->prev = prev;
		if (prev)
			prev->next = node;
		else
			copy = node;
		prev = node;
		original = original->next;
	}
	return (copy);
}

/* roi 0619
swaping of two nodes a and b in the list t_envir
temp_name and temp_value are just pointers to strings with already
 allocated memory in the node a*/
void	swap_nodes(t_envir *a, t_envir *b)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = a->var_name;
	tmp_value = a->var_value;
	a->var_name = b->var_name;
	a->var_value = b->var_value;
	b->var_name = tmp_name;
	b->var_value = tmp_value;
}

/* 
	roi 0619
	sorting by Bubble Sort algorithm.
	Code optimzed.
*/
static void	sort_envir_list(t_envir *list)
{
	int		swapped;
	t_envir	*ptr1;

	if (!list)
		return ;
	swapped = 1;
	ptr1 = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = list;
		while (ptr1->next)
		{
			if (strcmp(ptr1->var_name, ptr1->next->var_name) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
	}
}

/* 
 roi 0613
 */
t_envir	*copy_and_sort_envir_list(t_envir *original)
{
	t_envir	*copy;

	copy = copy_envir_list(original);
	sort_envir_list(copy);
	return (copy);
}
