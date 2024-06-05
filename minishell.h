/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:54 by oruban            #+#    #+#             */
/*   Updated: 2024/06/05 19:33:18 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h" // libft
# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv, EXIT_SUCCESS, EXIT_FAILURE
# include <unistd.h> // getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags
// # include "./includes/execute.h" // execute roi commented


typedef struct s_data
{
	struct s_token	*token_list;
	int				s_quote; /*shell is inside a single quoted string*/
	int				d_quote;
	int				forked; /*manage parent and child process behaviors*/
	int				count; /*count the number of tokens*/

	char			*input_minishell; /*initial input to the shell*/
	char			**root_directory; /*while be used later for parcing part*/
	char			*input_line; /*input after being processed*/

	//**********roi start**********
	// int				single_quote;
	// int				double_quote;
	struct s_tree	*tree;
	// t_heredoc_file	*heredoc_file;
	// t_envir			*env_list;
	// t_envir			*sorted_env_list;
	long int		exit_status;
	int				cmd_nbrs;
	int				pid;
	int				arg_nums;
	int				parenthesis_scope;
	char			*curr_dir;
	char			*exit_str;
	//******roi end****************
}				t_data;
 
typedef enum e_token_type
{
	T_WORD = 1,
	T_NEWLINE, /*\n*/
	T_SPACE, /*' '*/
	T_DOLLAR, /*$*/
	T_AMPER, /*&*/
	T_REDIR_INPUT, /*<*/
	T_REDIR_OUTPUT, /*>*/
	T_THREE_IN, /*<<<*/
	T_THREE_OUT, /*>>>*/
	T_IN_OUT, /*<>*/
	T_APPEND, /*>>*/
	T_PIPE, /*|*/
	T_OR, /*||*/
	T_AND, /*&&*/
	T_DELIMITER,
	T_PARENTHESES
}				t_token_type;

//**************roi start**************
typedef struct s_heredoc_file
{
	int						id;
	char					*filename;
	struct s_heredoc_file	*next;
}				t_heredoc_file;

typedef struct s_tree
{
	t_token_type	type;
	char			*value;
	char			**args_array;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_envir
{
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir;
//****************roi end****************

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

/*Loop into the minishell program*/
// void	minishell_loop(t_data *data);
int		minishell_loop(t_data *data);

/*freearr - free memory*/
void	free_2darray(char **array);

/*token_tree.c*/
//t_data *init_temp_data(void);

/*init_data.c*/
void	init_data(t_data **data, char **envp);

/*signal.c*/
int		handle_d(t_data *data, char *input);

/*free.c*/
void	free_data(t_data *data);

/*exit.c*/
void	exit_shell(char *message, int exit_code, t_data *data);

/*quote_checker*/
int		has_unclosed_quotes(char *str);
int		check_d_quote(char *s, int *i, int pos);
int		check_s_quote(char *s, int *i, int pos);
int		in_quotes(char *s, int pos);

/*str_checkers.c*/
char	*trim_input(char *input);
void	process_input(char *input, char *str, int *i, int *j);
int	ft_char_in_string(char c, char *str);

/*character_checkers.c*/
int		special_chars(char *str);

/*lexical_analysis.c*/
int	lexical_analysis(t_data *data, char *input);

/*lexical_analysis2.c*/
void	tokenise(t_data *data, char *str);

/*token_list_utils.c*/
void	add_token(t_token **head, t_token *new);

/*tokenising.c*/
t_token	*create_token(t_data *data, int i);
t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type);

/*quotes_utils.c*/
int	is_escaped(char *s, int pos);

/*find_token.c*/
int	find_token(t_data *data, char *str, int *i, t_token **head);
int	find_token2(int i, char *str, char *split);

/*parenthesis_utils2.c*/
void	set_token_parenth2(t_token *token);

//**********roi start**********
// execute.c
int	execute(t_data *data);
//**********roi end**********


#endif	//MINISHELL_H