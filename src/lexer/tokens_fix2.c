/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fix2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:36:47 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 11:05:56 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_tokens(t_token **head, t_data *data)
{
	find_or_tokens(head);
	find_and_tokens(head);
	find_in_out(head);
	find_three_out(head);
	find_three_in(head);
	find_asterisk(head, data);
}

void	find_append(t_token *current)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = current;
	if (tmp->type == T_REDIR_OUTPUT && tmp->next->type == T_REDIR_OUTPUT)
	{
		tmp->type = T_APPEND;
		ft_memdel(&tmp->word);
		tmp->word = ft_strdup(">>");
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		ft_memdel(&tmp2->word);
		free(tmp2);
	}
}

void	find_in_out(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_REDIR_INPUT && tmp->next->type == T_REDIR_OUTPUT)
		{
			tmp->type = T_IN_OUT;
			ft_memdel(&tmp->word);
			tmp->word = ft_strdup("<>");
			ft_memdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

/*remove tokens that have an empty string as their
'word' attribute, provided ther are not of the type 
'T_PARENTHESES'*/
void	clean_null_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (ft_strlen(tmp->word) == 0 && tmp->type != T_PARENTHESES)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			else
				*head = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			current = tmp->next;
			ft_memdel(&tmp->word);
			free(tmp);
		}
		else
			current = current->next;
	}
}

void	find_asterisk(t_token **head, t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_WORD)
		{
			if ((tmp->prev && tmp->prev->type == T_DELIM)
				|| (has_asterisk(tmp->word) && tmp->prev \
				&& tmp->prev->prev && tmp->prev->type == T_SPACE \
				&& tmp->prev->prev->type == T_DELIM))
				current = current->next;
			else if (has_asterisk(tmp->word))
				extend_asterisk(tmp, data);
		}
		current = current->next;
	}
}
