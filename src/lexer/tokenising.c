/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenising.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:18:57 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:34:00 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("\nword:%s:type:%d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

/*creates new token based on the input string with substr(start pos, subs len)*/
t_token	*create_token(t_data *data, int i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_shell("Error: Memory allocation failed\n", 1, data);
	new->word = ft_substr(data->input_line, i - data->count, data->count);
	new->type = T_WORD;
	data->count = 0;
	return (new);
}


/*creates new token based on the provided word and type*/
t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		exit_shell("Error: malloc failed\n", 1, data);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}

void	clean_space_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current != NULL)
	{
		tmp = current;
		if (tmp->type == T_SPACE)
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
