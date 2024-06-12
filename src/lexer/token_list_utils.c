/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:14:28 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:32:48 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*add new token to the end of a doubly linked list*/
void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new || !head)
		return ;
	if (*head)
	{
		tmp = *head;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
	{
		*head = new;
		new->prev = NULL;
		new->next = NULL;
	}
}

/*finds last token*/
t_token	*last_token(t_token *list)
{
	t_token	*tmp;
	
	tmp = list;
	if (tmp != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

