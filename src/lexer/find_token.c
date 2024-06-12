/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:02:56 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 11:32:07 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*creates and adds tokens to the token list*/
int	find_token(t_data *data, char *str, int *i, t_token **head)
{
	if (ft_char_in_string(str[*i], " \t") && !in_quotes(str, *i))
	{
		add_token(head, create_token(data, *i));
		if (str[*i] == ' ' || str[*i] == '\t')
			add_token(head, create_arg_token(data, " ", T_SPACE));
		(*i)++;
		data->count = 0;
		return (0);
	}
	else if (ft_char_in_string(str[*i], "|<>&") && !in_quotes(str, *i) && *i > 0
		&& !ft_char_in_string(str[*i - 1], "|<>&"))
		add_token(head, create_token(data, *i));
	return (1);
}

/*checks if a charecter at a given index in a string is
token delimeter*/
int	find_token2(int i, char *str, char *split)
{
	if (ft_char_in_string(str[i], split) && !in_quotes(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}
