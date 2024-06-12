/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:00:47 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:45:16 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*pair double pipe tokens into ||*/
void	find_or_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_PIPE && tmp->next->type == T_PIPE)
		{
			tmp->type = T_OR;
			ft_memdel(&tmp->word);
			tmp->word = ft_strdup("||");
			ft_memdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_and_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_AMPER && tmp->next->type == T_AMPER)
		{
			tmp->type = T_AND;
			ft_memdel(&tmp->word);
			tmp->word = ft_strdup("&&");
			ft_memdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_three_out(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_REDIR_OUTPUT && tmp->next->type == T_REDIR_OUTPUT)
			find_append(tmp);
		if (tmp->type == T_APPEND && tmp->next->type == T_REDIR_OUTPUT)
		{
			tmp->type = T_THREE_OUT;
			ft_memdel(&tmp->word);
			tmp->word = ft_strdup(">>>");
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			ft_memdel(&tmp2->word);
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_three_in(t_token **head)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*tmp2;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_REDIR_INPUT && tmp->next->type == T_REDIR_INPUT)
			find_delim(tmp);
		if (tmp->type == T_DELIM && tmp->next->type == T_REDIR_INPUT)
		{
			tmp->type = T_THREE_IN;
			ft_memdel(&tmp->word);
			tmp->word = ft_strdup("<<<");
			ft_memdel(&tmp->next->word);
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(tmp2);
		}
		current = current->next;
	}
}

void	find_delim(t_token *current)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = current;
	if (tmp->type == T_REDIR_INPUT && tmp->next->type == T_REDIR_INPUT)
	{
		tmp->type = T_DELIM;
		ft_memdel(&tmp->word);
		tmp->word = ft_strdup("<<");
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		ft_memdel(&tmp2->word);
		free(tmp2);
	}
}