/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:38:40 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:35:45 by beredzhe         ###   ########.fr       */
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
