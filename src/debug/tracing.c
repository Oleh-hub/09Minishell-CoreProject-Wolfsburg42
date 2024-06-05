/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:45 by oruban            #+#    #+#             */
/*   Updated: 2024/06/05 20:49:00 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*  Checking*/
/* 	typedef struct s_tree 
{
	t_token_type	type;
	char			*value;
	char			**args_array;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree; */

void out_t_tree(char *comment, t_tree *tree)
{
	printf ("%s\n", comment);
	printf("===============>start struct s_tree\n");
	printf("type: %d\n", tree->type);
	printf("value: %s\n", tree->value);
	printf("args_array: %p\n", tree->args_array);
	printf("left: %p\n", tree->left);
	printf("right: %p\n", tree->right);
	printf("==============>end struct s_tree\n");
}

/* Checking  */
/* typedef struct s_data {
	struct s_tree	*tree;
	struct s_token	*token_list;
	t_heredoc_file	*heredoc_file;
	t_envir			*env_list;
	t_envir			*sorted_env_list;
	int				single_quote;
	int				double_quote;
	long int		exit_status;
	int				cmd_nbrs;
	int				pid;
	int				count;
	int				arg_nums;
	int				parenthesis_scope;
	int				forked;
	char			*input_minishell;
	char			*input_line;
	char			*curr_dir;
	char			**root_directory;
	char			*exit_str;
}				t_data; */

void out_t_data_data(char *comment, t_data *data)
{
	printf("%s, t_data data\n", comment);
	printf("struct s_tree *tree		= %p\n", data->tree);
	if (data->tree)
		out_t_tree("", data->tree);
	printf("struct s_token *token_list	= %p\n", data->token_list);
	printf("t_heredoc_file *heredoc_file	= %p\n", data->heredoc_file);
	printf("t_envir *env_list		= %p\n", data->env_list);
	printf("t_envir *sorted_env_list	= %p\n", data->sorted_env_list);
	printf("int single_quote		= %d\n", data->single_quote);
	printf("int double_quote		= %d\n", data->double_quote);
	printf("long int exit_status		= %ld\n", data->exit_status);
	printf("int cmd_nbrs			= %d\n", data->cmd_nbrs);
	printf("int pid				= %d\n", data->pid);
	printf("int count			= %d\n", data->count);
	printf("int arg_nums			= %d\n", data->arg_nums);
	printf("int parenthesis_scope		= %d\n", data->parenthesis_scope);
	printf("int forked			= %d\n", data->forked);
	printf("char *input_minishell		= %s\n", data->input_minishell);
	printf("char *input_line		= %s\n", data->input_line);
	printf("char *curr_dir			= %s\n", data->curr_dir);
	printf("char **root_directory		= %p\n", data->root_directory);
	printf("char *exit_str			= %s\n", data->exit_str);
	
}

