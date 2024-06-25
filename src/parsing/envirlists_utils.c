/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirlists_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:08:15 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 21:11:10 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envclear(t_envir **lst)
{
	t_envir	*next;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_envdelone(*lst, free);
		*lst = next;
	}
}

void	ft_envdelone(t_envir *lst, void (*del))
{
	if (!lst || !del)
		return ;
	if (lst->var_name)
		free(lst->var_name);
	if (lst->var_value)
		free(lst->var_value);
	free(lst);
}
