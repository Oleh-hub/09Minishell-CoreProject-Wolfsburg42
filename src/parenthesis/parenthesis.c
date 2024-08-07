/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:49:41 by beredzhe          #+#    #+#             */
/*   Updated: 2024/07/03 12:43:23 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexic_with_parenth(t_data *data)
{
	int	flag;

	flag = find_parenthesis(data->input_line);
	if (flag)
	{
		if (flag == 2)
			return (1);
		free_tokens(&data->token_list, free);
		data->count = 0;
		tokenise_parenth(data, data->input_line);
		if (set_token_parenth(data))
			return (1);
	}
	return (0);
}

void	tokenize_parenth2(t_data *data, char *str, int *i, t_token ***head)
{
	while (str[*i])
	{
		if (!find_token3(data, str, i, *head))
			if (str[*i] != '(')
				continue ;
		if (str[*i] == '(' && !in_quotes(str, *i))
		{
			if (!find_parenth_token(data, str, i, *head))
			{
				(*i)++;
				continue ;
			}
		}
		data->count++;
		if (find_token2(*i, str, "|") || find_token2(*i, str, ">")
			|| find_token2(*i, str, "<") || find_token2(*i, str, "&")
			|| find_token2(*i, str, "$"))
			add_token(*head, create_token(data, *i + 1));
		(*i)++;
	}
}

void	tokenise_parenth(t_data *data, char *str)
{
	t_token	**head;
	int		i;

	i = 0;
	head = &data->token_list;
	tokenize_parenth2(data, str, &i, &head);
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}
