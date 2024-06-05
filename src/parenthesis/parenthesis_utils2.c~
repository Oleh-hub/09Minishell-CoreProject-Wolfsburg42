/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:04:01 by beredzhe          #+#    #+#             */
/*   Updated: 2024/05/30 11:11:49 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_parenth2(t_token *token)
{
	t_token	*head;

	head = token;
	if (!ft_strcmp(token->word, "<"))
		token->type = T_REDIR_INPUT;
	else if (!ft_strcmp(token->word, ">"))
		token->type = T_REDIR_OUTPUT;
	else if (!ft_strcmp(token->word, "|"))
		token->type = T_PIPE;
	else if (!ft_strcmp(token->word, "$"))
		token->type = T_DOLLAR;
	else if (!ft_strcmp(token->word, " "))
		token->type = T_SPACE;
	else if (!ft_strcmp(token->word, "&"))
		token->type = T_AMPER;
	else if (token->type != T_NEWLINE && token->type != T_PARENTHESES)
		token->type = T_WORD;
	token = head;
}