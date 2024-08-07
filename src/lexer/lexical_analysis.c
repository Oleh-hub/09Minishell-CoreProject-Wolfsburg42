/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:35:23 by beredzhe          #+#    #+#             */
/*   Updated: 2024/07/06 11:39:57 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*tokenizes the input string and sets the type of each token*/
int	lexical_analysis(t_data *data, char *input)
{
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (set_token_type(data))
		return (1);
	return (0);
}

int	lexical_analysis_tree(t_data *data, char *input)
{
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (set_token_type_tree(data))
		return (1);
	return (0);
}

int	set_token_type(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list, data);
	if (syntax_errors(data->token_list, data))
		return (data->exit_status = 258, 1);
	if (execute_delim(&data->token_list, data))
		return (g_child_pid = 0, 1);
	if (find_parenthesis(data->input_line))
		update_input_line(data);
	if (lexic_with_parenth(data))
		return (write(STDOUT_FILENO, "\n", 1), 1);
	clean_space_tokens(&data->token_list);
	concantenate_word_tokens(&data->token_list);
	return (0);
}

/*checks the 'word' field of a 't_token' structure and sets its
'type' */
void	set_token_type2(t_token *token)
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
	else if (token->type != T_NEWLINE)
		token->type = T_WORD;
	token = head;
}

int	set_token_type_tree(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens_tree(&data->token_list);
	if (lexic_with_parenth(data))
		return (1);
	clean_space_tokens(&data->token_list);
	concantenate_word_tokens(&data->token_list);
	return (0);
}
