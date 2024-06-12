/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:54 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 09:02:55 by oruban           ###   ########.fr       */
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


/* roi 0607
lis
char			*var_name;	//env NAME
char			*var_value;	//env VALUE
int				visible;	//if the variable is visible. It may not in a child
	*/
typedef struct s_envir
{
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir;
//****************roi end****************

typedef struct s_data
{
	struct s_token	*token_list;
	int				s_quote; /*shell is inside a single quoted string*/
	int				d_quote;
	long int		exit_status;
	int				forked; /*manage parent and child process behaviors*/
	int				count; /*count the number of tokens*/

	char			*input_minishell; /*initial input to the shell*/
	char			**root_directory; /*while be used later for parcing part*/
	char			*input_line; /*input after being processed*/

	//**********roi start**********
	// int				single_quote;
	// int				double_quote;
	struct s_tree	*tree;
	// t_heredoc_file	*heredoc_file; //roi 0608
	t_envir			*env_list;
	t_envir			*sorted_env_list;
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
	T_DELIM, /*<<*/
	T_PARENTHESES
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

/*Loop into the minishell program*/
void	minishell_loop(t_data *data);

/*find_token.c*/
int	find_token(t_data *data, char *str, int *i, t_token **head);
int	find_token2(int i, char *str, char *split);

/*tokens_fix.c*/
void	find_or_tokens(t_token **head);
void	find_and_tokens(t_token **head);
void	find_three_in(t_token **head);
void	find_delim(t_token *current);
void	find_three_out(t_token **head);

/*tokens_fix2.c*/
void	fix_tokens(t_token **head, t_data *data);
void	find_append(t_token *current);
void	find_in_out(t_token **head);
void 	clean_null_tokens(t_token **head);
void	find_asterisk(t_token **head, t_data *data);

/*lexical_analysis.c*/
int		lexical_analysis(t_data *data, char *input);
int		set_token_type(t_data *data);
void	set_token_type2(t_token *token);

/*lexical_analysis2.c*/
void	tokenise(t_data *data, char *str);

/*tokenising.c*/
void	print_tokens(t_data *data);
t_token	*create_token(t_data *data, int i);
t_token	*create_arg_token(t_data *data, char *word, enum e_token_type type);
void	clean_space_tokens(t_token **head);

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
void	free_tokens(t_token **begin, void (*del)(void *));

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
int		ft_char_in_string(char c, char *str);
int	ft_only_digit(char *str);

/*character_checkers.c*/
int		special_chars(char *str);

/*token_list_utils.c*/
void	add_token(t_token **head, t_token *new);

/*quotes_utils.c*/
int	is_escaped(char *s, int pos);

/*parenthesis_utils2.c*/
void	set_token_parenth2(t_token *token);

/*expand_utils.c*/
int		has_asterisk(char *str);
char	*update_aster_temp(char *temp, char *root_directory_k);
void	check_matches(t_token *token, char **root_directory);

/*execution_utils.c*/
int	is_only_asterisks(char *str);

/*expand_asterisk.c*/
void	update_asterisk_token(t_token *token, t_data *data);
void	extend_asterisk(t_token *token, t_data *data);
int		match_pattern(const char *pattern, const char *string);

/*syntax_errors.c*/
char	*check_first_token(char *str, int *i);
char	*check_first_half(char *str, int *i);
char	*check_second_half(char *str, int *i);
int		syntax_errors(t_token *token, t_data *data);
int		check_and(t_token *token, char *str);

/*redir_general_errors.c*/
int	check_inout(t_token *token);
int	check_numbers(t_token *tmp);
int	check_red_general(t_token *tmp);
int	check_first_half_general(t_token *tmp);
int	check_second_half_general(t_token *tmp);

/*redin_errors.c*/
int 	check_red(t_token *token, char *str);
int		check_red_in(t_token *token);
int		check_redin_first_half(t_token *token);
int		check_redin_second_half(t_token *token);
int		check_redin_last_part(t_token *token);

/*delim_append_errors.c*/
int	check_delim(t_token *token);
int	check_first_half_delim(t_token *token);
int	check_second_half_delim(t_token *token);
int	check_append(t_token *token);

/*token_errors.c*/
int	check_pipe_or(t_token *tmp);
int	check_first_half_pipe_or(t_token *tmp);
int	check_second_half_pipe_or(t_token *tmp);
int	check_threein(t_token *token);
int	check_threeout(t_token *token);

/*redout_erros.c*/
int	check_red_out(t_token *token);
int	check_first_half_out(t_token *token);
int	check_second_half_out(t_token *token);
int	check_last_part_out(t_token *token);

#endif