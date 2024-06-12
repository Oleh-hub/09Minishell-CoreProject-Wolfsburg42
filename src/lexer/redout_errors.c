/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redout_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:52:22 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/11 15:03:41 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_first_half_out(t_token *token)
{
	if (token->next->type == T_IN_OUT)
		return (printf("minishell: syntax error near %s\n", \
		"unexpected token `<>'"), 1);
	if (token->next->type == T_AND)
	{
		if (token->next->next->type == T_AMPER
			|| token->next->next->type == T_AND)
			return (printf("minishell: syntax error near %s\n", \
			"unexpected token `&&'"), 1);
		if (token->next->next->type == T_REDIR_OUTPUT)
			return (printf("minishell: syntax error near %s\n", \
			"unexpected token `&>'"), 1);
		if (token->next->next->type != T_AMPER
			|| token->next->next->type == T_AND)
			return (printf("minishell: syntax error near %s\n", \
			"unexpected token `&'"), 1);
	}
	return (0);
}

int	check_second_half_out(t_token *token)
{
	if (token->next->type == T_OR && (token->next->next->type == T_PIPE
			|| token->next->next->type == T_OR))
		return (printf("minishell: syntax error near %s\n", \
		"unexpected token `||'"), 1);
	if (token->next->type == T_OR)
		return (printf("minishell: syntax error near %s\n", \
		"unexpected token `|'"), 1);
	return (0);
}

int	check_last_part_out(t_token *token)
{
	if (token->next->type == T_PIPE)
	{
		if (token->next->next->type == T_SPACE)
			if (check_red_general(token->next->next))
				return (1);
		if (check_red_general(token->next))
			return (1);
	}
	if (token->next->type == T_AMPER)
		if (check_red_general(token->next))
			return (1);
	if (token->next->type == T_SPACE)
		if (check_red_general(token->next))
			return (1);
	if (check_red_general(token))
		return (1);
	return (0);
}

int	check_red_out(t_token *token)
{
	int	result;

	result = 0;
	if (token->type == T_REDIR_OUTPUT)
	{
		if ((token->next->type == T_SPACE && token->next->next->type == T_WORD)
			|| token->next->type == T_WORD)
			return (0);
		result = check_first_half_out(token);
		if (result != 0)
			return (result);
		result = check_second_half_out(token);
		if (result != 0)
			return (result);
		result = check_last_part_out(token);
		if (result != 0)
			return (result);
	}
	return (result);
}