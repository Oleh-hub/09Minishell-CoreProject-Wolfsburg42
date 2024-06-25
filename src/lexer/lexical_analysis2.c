/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:38:40 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/20 13:57:16 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*breaking down a given string into tokens*/
void	tokenise(t_data *data, char *str)
{
	int		i;
	t_token	**head;

	i = 0;
	head = &data->token_list;
	data->count = 0;
	while (str[i])
	{
		if (!find_token(data, str, &i, head))
			continue ;
		data->count++;
		if (find_token2(i, str, "|") || find_token2(i, str, ">")
			|| find_token2(i, str, "<") || find_token2(i, str, "&"))
			add_token(head, create_token(data, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}

/*merges adjacent tokens in a linked list*/
static void	handle_append_and_redirection(t_token **tmp)
{
	t_token	*tmp2;

	if ((*tmp)->next && (*tmp)->next->type == T_WORD)
	{
		ft_memdel(&(*tmp)->word);
		(*tmp)->word = ft_strdup((*tmp)->next->word);
		ft_memdel(&(*tmp)->next->word);
		tmp2 = (*tmp)->next;
		(*tmp)->next = tmp2->next;
		if ((*tmp)->next)
			(*tmp)->next->prev = *tmp;
		free(tmp2);
	}
}

static void	handle_word_concatenation(t_token **tmp)
{
	t_token	*tmp2;
	char	*str;

	if ((*tmp)->word)
		return ;
	str = malloc(sizeof(char) * (ft_strlen((*tmp)->word) + \
	ft_strlen((*tmp)->next->word) + 2));
	ft_strcpy(str, (*tmp)->word);
	ft_strcat(str, " ");
	ft_strcat(str, (*tmp)->next->word);
	ft_memdel(&(*tmp)->word);
	(*tmp)->word = str;
	tmp2 = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = *tmp;
	ft_memdel(&tmp2->word);
	free(tmp2);
}

/*making sure that tokens are appropriately processed and
combined where necessary*/
void	concantenate_word_tokens(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp && tmp->next != NULL && tmp->next->type != T_NEWLINE)
	{
		if (tmp->type == T_APPEND || tmp->type == T_REDIR_INPUT
			|| tmp->type == T_REDIR_OUTPUT || tmp->type == T_IN_OUT
			|| tmp->type == T_THREE_IN || tmp->type == T_DELIM)
			handle_append_and_redirection(&tmp);
		if (tmp->type == T_WORD && tmp->next && tmp->next->type == T_WORD)
			handle_word_concatenation(&tmp);
		tmp = tmp->next;
	}
}
