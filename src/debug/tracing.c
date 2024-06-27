/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:45 by oruban            #+#    #+#             */
/*   Updated: 2024/06/27 08:53:31 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// printf("\033[34mLooking for SEGFAULT\033[0m\n");

/* Checking 
typedef struct s_envir {
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir; */

void out_t_envir(char *comment, t_envir *env_list)
{
	printf("\033[34m");
	printf("====>start struct s_envir %s\n", comment);
	while (env_list)
	{
		printf("(char *) env_list->var_name	= %s\n", env_list->var_name);
		printf("(char *) env_list->var_value	= %s\n", env_list->var_value);
		printf("(int) env_list->visible		= %d\n", env_list->visible);
		printf("(struct s_envir *) env_list->next	= %p\n", env_list->next);
		printf("(struct s_envir *) env_list->prev	= %p\n", env_list->prev);
		env_list = env_list->next;
	}
	printf("====>end struct s_envir\n");
	printf("\033[0m");
	printf("\n");
}

/*  Checking*/
/* 	typedef struct s_tree 
{
	t_token_type	type;
	char			*value;
	char			**args_array; // command with all arguments
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree; */

void out_t_tree(char *comment, t_tree *tree)
{
	printf ("\033[34m");
	printf("====>start struct s_tree %s\n", comment);
	while (tree)
	{
		printf("(t_token_type	*)tree->type		= %d\n", tree->type);
		printf("(char		*)tree->value		= %s\n", tree->value);
		printf("(char		**)tree->args_array	= %p\n", tree->args_array);
		if (tree->args_array)
		{
			int i = 0;
			while (tree->args_array[i])
			{
				printf("tree->args_array[%d]		= %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		printf("(struct s_tree	*)tree->left		= %p\n", tree->left);
		printf("(struct s_tree	*)tree->right		= %p\n", tree->right);
		tree = tree->right;
	}
	printf("====>end struct s_tree *tree\n");
	printf ("\033[0m");
	printf("\n");
}

/* Checking  */
/* typedef struct s_data {
	struct s_tree	*tree;
	struct s_token	*token_list;
	t_heredoc_file	*heredoc_file;
	t_envir			*env_list;
	t_envir			*sorted_env_list;
	int				s_quote;
	int				d_quote;
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
	// printf("struct s_tree *tree		= %p %s\n", data->tree, comment);
	printf("(struct s_tree *) data->tree		= %p\n", data->tree);
	if (data->tree)
		out_t_tree("*tree", data->tree);
	printf("(struct s_token *) data->token_list	= %p\n", data->token_list);
	printf("(t_heredoc_file *) data->heredoc_file	= %p\n", data->heredoc_file);
	printf("(t_envir *) data->env_list		= %p\n", data->env_list);
	if (data->env_list)
		out_t_envir("data->env_list", data->env_list);
	printf("(t_envir *) data->sorted_env_list	= %p\n", data->sorted_env_list);
	printf("int data->s_quote			= %d\n", data->s_quote);
	printf("(int) data->d_quote		= %d\n", data->d_quote);
	printf("(long) int data->exit_status		= %ld\n", data->exit_status);
	printf("(int) data->cmd_nbrs			= %d\n", data->cmd_nbrs);
	printf("(int) data->pid				= %d\n", data->pid);
	printf("(int) data->count			= %d\n", data->count);
	printf("(int) data->arg_nums			= %d\n", data->arg_nums);
	printf("(int) data->parenthesis_scope		= %d\n", data->parenthesis_scope);
	printf("(int) data->forked			= %d\n", data->forked);
	printf("(char *) data->input_minishell		= %s\n", data->input_minishell);
	printf("(char *) data->input_line		= %s\n", data->input_line);
	printf("(char *) data->curr_dir			= %s\n", data->curr_dir);
	printf("(char *) root_directory		= %p\n", data->root_directory);
	printf("(char *) data->exit_str			= %s\n", data->exit_str);
	printf("====>end struct s_data\n");
}

/* roi 0614
	printing out the 2d array 
 */
void out_oochar(char *comment, char **temp)
{
	printf ("\033[34m");
	printf("==%s==>\n", comment);
	while (*temp)
		printf("'%s' ", *temp++);
	printf ("\033[0m");
	printf("\n");
}
