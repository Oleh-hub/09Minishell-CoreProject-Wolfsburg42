/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tree_roots.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:17:12 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 21:30:07 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_token_type(t_token *token, int *pipe, t_token **pipetoken)
{
	if (token->type == T_OR || token->type == T_AND || token->type == T_PIPE)
	{
		if (token->type == T_OR)
			return (token);
		if (token->type == T_AND)
			return (token);
		if (token->type == T_PIPE)
		{
			*pipe = 1;
			*pipetoken = token;
		}
	}
	return (NULL);
}

/*helping to determine the primary operation (like &&, ||, |)
in a command line, which affects how commands are executed.
They process tokens to identify logical and pipe operators,
which are key to building the execution tree for the shell.*/
t_token	*find_first_root(t_token **root_token)
{
	t_token	*token;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	token = *root_token;
	pipetoken = NULL;
	pipe = 0;
	while (token && token->next && token->next->type != T_NEWLINE)
	{
		result = handle_token_type(token, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		token = token->next;
	}
	if (pipe)
		return (pipetoken);
	return (*root_token);
}

/*In summary, the find_tree_root_right function is used to determine
the appropriate root token for constructing a parse tree in a
shell-like environment. It prioritizes logical operators and pipes
but defaults to the initial token if none of these are found,
provided the token isn't a "boundary". This ensures that the parse
tree is built correctly according to the precedence of operations.*/
t_token	*find_tree_root_right(t_token **root_token)
{
	t_token	*token;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	token = *root_token;
	pipetoken = NULL;
	pipe = 0;
	if (!token || !ft_strcmp(token->word, "boundary"))
		return (NULL);
	while (token && token->next && token->next->type != T_NEWLINE
		&& ft_strcmp(token->next->word, "boundary"))
	{
		result = handle_token_type(token, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		token = token->next;
	}
	if (pipe)
		return (pipetoken);
	return (*root_token);
}

t_token	*find_tree_root_left(t_token **root_token)
{
	t_token	*token;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	token = *root_token;
	pipetoken = NULL;
	pipe = 0;
	if (!token || !ft_strcmp(token->word, "boundary"))
		return (NULL);
	while (token != NULL && token->prev != NULL
		&& ft_strcmp(token->prev->word, "boundary"))
	{
		result = handle_token_type(token, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		token = token->prev;
	}
	if (pipe)
		return (pipetoken);
	return (token);
}
