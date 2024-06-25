/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:17:28 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 11:17:42 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces_parenth(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '(' && str[i] != ')')
			return (0);
		i++;
	}
	return (1);
}

int	token_len(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		if (token->type != T_NEWLINE)
			len++;
		token = token->next;
	}
	return (len);
}
