/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirlists_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:59:33 by oruban            #+#    #+#             */
/*   Updated: 2024/06/25 20:26:21 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
roi 0611
the funciton inerates the enviroment list 
by exacuting an inetration via function f() over the curent node 
of the list lst and goes to the next node to do the same.
The result: all nodes staring from the indicated as argumetn lst and till 
the end of the list will be processed by the function f()
*/
void	ft_enviter(t_envir *lst, int fd_out, void (*f)(t_envir *, int))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst, fd_out);
		lst = lst->next;
	}
}

t_envir	*ft_envlast(t_envir *lst)
{
	t_envir	*node;

	node = lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
	}
	return (node);
}

/* 
	roi 0619
	memory allocation and 0 initiation for a node of data type type t_envir,
	holding envirenment variable data
 */
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

int	ft_envsize(t_envir *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
