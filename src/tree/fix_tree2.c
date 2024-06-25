/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tree2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:30:27 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 11:34:29 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_tree(t_tree **tree)
{
	fix_command(tree);
	fix_redirection(tree);
}

void	connect_nodes(t_tree **temp_redir, t_tree *temp2)
{
	t_tree	*last_redir;

	if (*temp_redir == NULL)
	{
		*temp_redir = temp2;
		(*temp_redir)->right = NULL;
	}
	else
	{
		last_redir = *temp_redir;
		while (last_redir->right)
			last_redir = last_redir->right;
		last_redir->right = temp2;
		temp2->right = NULL;
	}
}

void	process_tree_nodes(t_tree **tree)
{
	t_tree	*temp;
	t_tree	*temp_redir;
	t_tree	*temp2;

	temp = *tree;
	temp_redir = (*tree)->left;
	while (temp && temp->right && temp->right->type != T_NEWLINE)
	{
		if (temp->right->type == T_DELIM || temp->right->type == T_REDIR_INPUT)
		{
			temp2 = temp->right;
			temp->right = temp2->right;
			connect_nodes(&temp_redir, temp2);
		}
		else
			temp = temp->right;
	}
	(*tree)->left = temp_redir;
}

void	fix_redirection(t_tree **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->type == T_WORD)
		process_tree_nodes(tree);
	else
	{
		fix_redirection(&(*tree)->left);
		fix_redirection(&(*tree)->right);
	}
}

void	fix_command(t_tree **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->type == T_APPEND || (*tree)->type == T_DELIM
		|| (*tree)->type == T_REDIR_INPUT || (*tree)->type == T_REDIR_OUTPUT
		|| (*tree)->type == T_WORD)
		process_fix_com(tree);
	else
	{
		fix_command(&(*tree)->left);
		fix_command(&(*tree)->right);
	}
}
