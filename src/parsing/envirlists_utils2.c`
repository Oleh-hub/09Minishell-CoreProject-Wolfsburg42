/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirlists_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:59:33 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 07:51:31 by oruban           ###   ########.fr       */
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
