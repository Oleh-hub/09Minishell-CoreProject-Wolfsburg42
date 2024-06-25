/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 08:57:48 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 10:18:39 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The init_tree_one_parenth function is responsible for initializing
the syntax tree when the root token is a parenthesis. It updates the
input line, performs lexical analysis, and sets the root of the tree
accordingly.*/
int	init_tree_one_parenth(t_data *data, t_token **root_token, t_token **head)
{
	ft_memdel(&data->input_line);
	data->input_line = ft_strdup((*root_token)->word);
	free_tokens(&data->token_list, free);
	if (lexical_analysis(data, data->input_line))
		return (1);
	*root_token = find_first_root(head);
	data->tree->type = (*root_token)->type;
	data->tree->value = ft_strdup((*root_token)->word);
	ft_memdel(&(*root_token)->word);
	(*root_token)->word = ft_strdup("boundary");
	if (data->tree->type == T_WORD)
	{
		data->tree->args_array = ft_split_args(data->tree->value, ' ');
		find_quotes(data->tree->args_array, data);
	}
	return (0);
}

/*The init_tree function initializes and builds a syntax
tree from a list of tokens. The syntax tree represents
the hierarchical structure of commands to be executed by the shell.*/
int	init_tree(t_data *data, t_token **head)
{
	t_token	*root_token;

	data->tree = init_tree_root();
	root_token = find_first_root(head);
	if (root_token->type == T_PARENTHESES)
	{
		if (init_tree_one_parenth(data, &root_token, head))
			return (1);
	}
	else
	{
		data->tree->type = root_token->type;
		data->tree->value = ft_strdup(root_token->word);
		if (root_token->type == T_WORD)
		{
			data->tree->args_array = ft_split_args(root_token->word, ' ');
			find_quotes(data->tree->args_array, data);
		}
		free(root_token->word);
		root_token->word = ft_strdup("boundary");
	}
	if (built_tree(&data->tree, root_token, data))
		return (1);
	return (0);
}
