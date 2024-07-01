/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:32:54 by oruban            #+#    #+#             */
/*   Updated: 2024/07/01 17:08:17 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef SA_RESTART
# define SA_RESTART 0
#endif

#ifndef SA_SIGINFO
# define SA_SIGINFO 0
#endif

# define _POSIX_C_SOURCE 200809L
# include <signal.h> // sigaction
# include "libft/libft.h" // libft
# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv, EXIT_SUCCESS, EXIT_FAILURE
# include <unistd.h> // getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <fcntl.h> // open flags
# include <string.h>
# include <termios.h> // POSIX terminal control definitions
# include <dirent.h> // opening, reading directory
# include <termcap.h> // terminal handling as terminal clearing
# include <stdint.h>
# include <limits.h> //INT_MAX
# include <errno.h> // defines macros for reporting and retrieving errors
# include <stdbool.h> // boolean type

/* 
	roi 0612
	enumarated every token just for cnovenience
 */
typedef enum e_token_type
{
	T_WORD			= 1,
	T_NEWLINE		= 2,	/*\n*/
	T_SPACE			= 3,	/*' '*/
	T_DOLLAR		= 4,	/*$*/
	T_AMPER			= 5,	/*&*/
	T_REDIR_INPUT	= 6,	/*<*/
	T_REDIR_OUTPUT	= 7,	/*>*/
	T_THREE_IN		= 8,	/*<<<*/
	T_THREE_OUT		= 9,	/*>>>*/
	T_IN_OUT		= 10,	/*<>*/
	T_APPEND		= 11,	/*>>*/
	T_PIPE			= 12,	/*|*/
	T_OR			= 13,	/*||*/
	T_AND			= 14,	/*&&*/
	T_DELIM			= 15,	/*<<*/
	T_PARENTHESES	= 16	/*()*/
}			t_token_type;

// typedef enum e_token_type
// {
// 	T_WORD = 1,
// 	T_NEWLINE, /*\n*/
// 	T_SPACE, /*' '*/
// 	T_DOLLAR, /*$*/
// 	T_AMPER, /*&*/
// 	T_REDIR_INPUT, /*<*/
// 	T_REDIR_OUTPUT, /*>*/
// 	T_THREE_IN, /*<<<*/
// 	T_THREE_OUT, /*>>>*/
// 	T_IN_OUT, /*<>*/
// 	T_APPEND, /*>>*/
// 	T_PIPE, /*|*/
// 	T_OR, /*||*/
// 	T_AND, /*&&*/
// 	T_DELIM, /*<<*/
// 	T_PARENTHESES /*()*/
// }				t_token_type;

/* roi 0607
lis
char			*var_name;	//env NAME
char			*var_value;	//env VALUE
int				visible;	// if visible =1 it can me seen by 'env', 
							// otherwise -> only by 'export'
							// Asumption: It may not in a child
	*/

typedef struct s_envir 
{
	char		*var_name;
	char		*var_value;
	int			visible;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir;


/* 
	roi 0609
	the elemetn 'char *value' is a bit excessive, because it is always equal to
	'char	*args_array[1]'

	char			*value;			// value  always == args_array[0]
	char			**args_array;	// command with all arguments like 
									//'cd /home/username jkl'
 */
typedef struct s_tree
{
	t_token_type	type;
	char			*value;
	char			**args_array;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_heredoc_file 
{
	int						id;
	char					*filename;
	struct s_heredoc_file	*next;
}				t_heredoc_file;

typedef struct s_data
{
	struct s_tree	*tree;
	struct s_token	*token_list;
	int				s_quote; /*shell is inside a single quoted string*/
	t_heredoc_file	*heredoc_file;
	t_envir			*env_list;
	t_envir			*sorted_env_list;
	int				d_quote;
	long int		exit_status;
	int				pid;
	int				forked; /*manage parent and child process behaviors*/
	int				count; /*count the number of tokens*/
	char			*input_minishell; /*initial input to the shell*/
	char			*curr_dir;
	char			**root_directory; /*while be used later for parcing part*/
	char			*input_line; /*input after being processed*/
	char			*exit_str;
	int				cmd_nbrs;
	int				arg_nums;
	int				parenthesis_scope;

}				t_data;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_heredoc_info
{
	char	*filename;
	int		heredoc_count;
	char	*token;
	char	*limiter;
}			t_heredoc_info;

typedef struct s_copy_params
{
	char			**new_input_line;
	int				*i;
	int				*j;
	t_heredoc_file	**current_file;
}				t_copy_params;

typedef struct s_find_command
{
	t_tree	*tmp;
	t_tree	*tmp2;
	t_tree	*address;
	t_tree	*f_nontokw;
	t_tree	*l_nontokw;
	char	**command;
}				t_find_command;

typedef struct s_tokenise_tree
{
	t_token	*head;
	t_token	*tail;
	t_token	*temp;
	t_token	*atach_left;
	t_token	*atach_right;
	t_data	*temp_data;
	t_token	*new_tokens;
}				t_tokenise_tree;

/* 
	roi 0621
	strucnture needed for pipe '|' handling
 */
typedef struct s_pipe_info
{
	int		*pipe_fd;
	t_data	*data;
	t_tree	*tree;
	int		end;
	int		std_fd;
}				t_pipe_info;

/* 
	roi 0626
	strucnture created to facilitate execute_command() function
	that execting the external shell command
 */
typedef struct s_command_args
{
	t_data	*data;
	t_tree	*tree;
	char	*exec_path;
	int		fd_inp;
	int		fd_out;
}				t_command_args;

/*Loop into the minishell program*/
void	minishell_loop(t_data *data);
char	**create_envp(void);

/*reset.c*/
void	reset_data(t_data *data);

/*find_token.c*/
int		find_token(t_data *data, char *str, int *i, t_token **head);
int		find_token2(int i, char *str, char *split);

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
int		lexical_analysis_tree(t_data *data, char *input);
int		set_token_type(t_data *data);
void	set_token_type2(t_token *token);
int		set_token_type_tree(t_data *data);

/*lexical_analysis2.c*/
void	tokenise(t_data *data, char *str);
void	concantenate_word_tokens(t_token **head);

/*tokenising.c*/
void		print_tokens(t_data *data);
t_token		*create_token(t_data *data, int i);
t_token		*create_arg_token(t_data *data, char *word, enum e_token_type type);
void		clean_space_tokens(t_token **head);
void		fix_tokens_tree(t_token **head);

/*freearr - free memory*/
void	free_2darray(char **array);
void	free_tree(t_tree **tree);

/*init_data.c*/
void	init_data(t_data **data, char **envp);

/*signal.c*/
void	handle_signal(void);
void	handle_sigint(int signo);
void	handle_sigtstp_sigquit(int signo);
void	handle_c(int signo);
int		handle_d(t_data *data, char *input);

/*free.c*/
void	free_data(t_data *data);
void	free_tokens(t_token **begin, void (*del)(void *));
void	free_temp_data(t_data *data);
void	free_heredoc_files(t_heredoc_file *head);

/*exit.c*/
void	exit_shell(char *message, int exit_code, t_data *data);

/*quote_checker*/
void	find_quotes(char **str, t_data *data);
int		has_unclosed_quotes(char *str);
int		check_d_quote(char *s, int *i, int pos);
int		check_s_quote(char *s, int *i, int pos);
int		in_quotes(char *s, int pos);

/*str_checkers.c*/
char	*trim_input(char *input);
void	process_input(char *input, char *str, int *i, int *j);
int		ft_char_in_string(char c, char *str);
int		ft_only_digit(char *str);

/*character_checkers.c*/
int		special_chars(char *str);

/*token_list_utils.c*/
void	add_token(t_token **head, t_token *new);

/*quotes_utils.c*/
int		is_escaped(char *s, int pos);
int		has_quotes(char *str);
int		has_dollar(char *str);

/*check_valid_env.c*/
int		is_valid_env_char(char c);

/*expand_quotes_dollar.c*/
char	*expand_quotes(t_data *data, char *s);
char	*expand_dollar_and_join(t_data *data, char *s, int *i, char *result);
char	*expand_dollar(t_data *data, char *s, int *i);
char	*expand_d_quotes(t_data *data, char *s, int *i, char *result);
char	*expand_s_quotes(char *s, int *i, char *result);


/*update_input_line.c*/
void	update_input_line(t_data *data);
void 	copy_filename(t_data *data, t_copy_params *params);

/*parenthesis.c*/
int		lexic_with_parenth(t_data *data);
void	tokenize_parenth2(t_data *data, char *str, int *i, t_token ***head);
void	tokenise_parenth(t_data *data, char *str);

/*parenthesis_utils.c*/
int		only_parenth(char *str);
int		operand_error_parenth(int i);
int		count_parenthesis(char *str, int *parenCount, int *parenth_total);
int		check_parenthesis(int parenCount, int parenth_total);
int		find_parenthesis(char *str);


/*parenthesis_utils2.c*/
int		set_token_parenth(t_data *data);
void	set_token_parenth2(t_token *token);
int		find_parenth_token(t_data *data, char *str, int *i, t_token **head);
int		find_token3(t_data *data, char *str, int *i, t_token **head);
t_token	*create_parenth_token(t_data *data, int i, char *input);

/*parenthesis_errors.c*/
int		syntax_error_parenth(t_token **token);
int		check_prev_token(t_token **token);
int		check_next_token(t_token **token);

/*expand_utils.c*/
int		has_asterisk(char *str);
char	*update_aster_temp(char *temp, char *root_directory_k);
void	check_matches(t_token *token, char **root_directory);
char	*process_dquote(t_data *data, char *s, int *i, char *result);
char	*process_squote(char *s, int *i, char *result);

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
int		check_inout(t_token *token);
int		check_numbers(t_token *tmp);
int		check_red_general(t_token *tmp);
int		check_first_half_general(t_token *tmp);
int		check_second_half_general(t_token *tmp);

/*redin_errors.c*/
int 	check_red(t_token *token, char *str);
int		check_red_in(t_token *token);
int		check_redin_first_half(t_token *token);
int		check_redin_second_half(t_token *token);
int		check_redin_last_part(t_token *token);

/*delim_append_errors.c*/
int		check_delim(t_token *token);
int		check_first_half_delim(t_token *token);
int		check_second_half_delim(t_token *token);
int		check_append(t_token *token);

/*token_errors.c*/
int		check_pipe_or(t_token *tmp);
int		check_first_half_pipe_or(t_token *tmp);
int		check_second_half_pipe_or(t_token *tmp);
int		check_threein(t_token *token);
int		check_threeout(t_token *token);

/*redout_erros.c*/
int		check_red_out(t_token *token);
int		check_first_half_out(t_token *token);
int		check_second_half_out(t_token *token);
int		check_last_part_out(t_token *token);

/*root_directory.c*/
char	**read_directory(DIR *d, char **root_directory);
char	**get_root_directory(void);
void	sort_directory(char **arr);
int		count_root_directory(void);

/*envir_list.c*/
void	extract_env_var(t_envir *envir, char *env);
t_envir	*fill_env(char **env, t_data *data);

/*envirlists_utils2.c*/
t_envir	*ft_envnew(void);

/*execute_delim.c*/
int		execute_delim(t_token **head, t_data *data);
int		handle_heredoc(t_data *data, t_token *current, t_heredoc_info *info);
int		process_heredoc(t_heredoc_info *info, t_data *data);
int		handle_heredoc_input(t_heredoc_info *info, int fd, char **old_filename);
void	create_temp_filename(t_heredoc_info *info);

/*execute_delim_utils.c*/
void	add_heredoc_file(t_data *data, char *filename, int id);
void	free_heredoc_info(t_heredoc_info *info);

/*tree_init.c*/
int		init_tree(t_data *data, t_token **head);
int		init_tree_one_parenth(t_data *data, t_token **root_token, t_token **head);


// /*tree_utils.c*/
t_tree	*init_tree_root(void);

/*find_tree_roots.c*/
t_token	*find_first_root(t_token **root_token);
t_token	*handle_token_type(t_token *token, int *pipe, t_token **pipetoken);
t_token	*find_tree_root_right(t_token **root_token);
t_token	*find_tree_root_left(t_token **root_token);

/*utils2.c*/
char	*ignore_spaces(char *input);
int		is_only_ascii(char *str);
char	**dup_2darray(char **array);
int	len_2darray(char **array);
int	is_char_in_str(char c, char *str);

/*utils3.c*/
int	only_spaces_parenth(char *str);
/* int	token_len(t_token *token); */

/*utils4.c*/
char	**ft_split_args(char *s, char c);
int		ft_arrarr_args(char **arr, char *s, char c, int str);
int		ft_countarr_args(char *s, char c);

/*command.c*/
t_envir	*find_envir_variable(t_data *data, char *var_name, int len);

/*built_tree.c*/
int	built_tree(t_tree **tree, t_token *address, t_data *data);

/*tokenise_for_tree.c*/
int tokenise_for_tree(t_token *t_parenth, t_data *data);
t_data *init_temp_data(void);
t_token	*copy_tokens(t_token *head);

/*tokenise_for_tree_utils.c*/
void	initialize_vars(t_tokenise_tree *vars, t_token *t_parenth);
int		handle_lexical_analysis(t_tokenise_tree *vars);
void	find_tail(t_tokenise_tree *vars);
void	handle_atach_left(t_tokenise_tree *vars, t_data *data);
void	handle_atach_right(t_tokenise_tree *vars);

/*envirlists_utils.c*/
void	ft_envclear(t_envir **lst);
void	ft_envdelone(t_envir *lst, void (*del));

/* envirlists_utils2.c */
void		ft_enviter(t_envir *lst, int fd_out, void (*f)(t_envir *, int));
t_envir		*ft_envlast(t_envir *lst);
t_envir		*ft_envnew(void);
int			ft_envsize(t_envir *lst);

/*shlvl.c*/
void	incr_shell_lvl(t_data *data);

/*fix_tree.c*/
void	process_fix_com(t_tree **tree);
void	find_command(t_tree **tree);
void	update_non_tword_nodes(t_tree **f_nontokw, t_tree **l_nontokw, \
	t_tree **tmp, t_tree **tmp2);
void	update_tword_node(t_tree *address, t_tree **tmp, t_tree **tmp2);

/*fix_tree2.c*/
void	fix_tree(t_tree **tree);
void	fix_command(t_tree **tree);
void	fix_redirection(t_tree **tree);
void	process_tree_nodes(t_tree **tree);
void	connect_nodes(t_tree **temp_redir, t_tree *temp2);

/*join2d_arrays.c*/
char	**join2darrays(char **str1, char **str2);

/* environment.c */
void		print_env_node(t_envir *env_node, int fd_out);
void		print_env_node_sorted(t_envir *env_node, int fd_out);
void		free_envir_array(char **env_array);

/* execute_buildins.c */
int			is_builtin(char *cmd);
int			execute_builtin(t_data *data, t_tree *tree, int fd_out);
int			check_echo(t_data *data, t_tree *tree, int fd_out);

/* execute_buildins2.c */
// char		*get_curr_dir(void);
// char		*get_home_dir(void);
int			execute_pwd(t_data *data);
void		execute_exit(t_data *data, t_tree *tree); // does not return
// anything to the programm, only to the system
void		execute_env(t_envir **env, int fd_out);

/* execute_buildins3.c */
int			execute_cd(t_data *data, char *path);
int			execute_unset(t_data *data, t_tree *tree);

/* execute_export.c */
int			execute_export(t_data *data, t_tree *tree, int fd_out);
void		handle_existing_variable(t_envir *temp, char *var_value);
void	handle_visible_variable(t_envir *temp);
void		handle_new_variable(t_envir **env_list, char *var_name, \
char *var_value);
void		export(t_envir **env_list, char *var_name, char *var_value, \
t_data *data);

/* execute_echo.c */
int			echo_handle_option(char **args);
int			execute_echo(char *args[], int fd_out);

/* execute.c */
int			execute(t_data *data);
int			execute_and_handle_files(t_data *data, t_tree *tree);
int			evaluate_execution(t_data *data, t_tree *tree);
// int			execute_logic(t_data *data, t_tree *tree); // || and && handling roi 0621

/* execute_redout.c */
int			get_output_file(t_tree *tree);

/* execute_redin.c */
int			get_input_file(t_tree *tree);

/* execute_word.c */
int			execute_word(t_data *data, t_tree *tree, int fd_inp, int fd_out);
int			execute_command(t_data *data, t_tree *tree, int fd_inp, int fd_out);
char		**env(t_envir **lst);
// void		fill_envp(char **envp, t_envir **lst); // roi 0623 made static
// void		print2darray(char **array); // roi 0623 debuggin funciton

/* execute_pipe.c */
int			execute_pipe(t_data *data, t_tree *tree);

/* execute_utils.c */
// int			is_logic_root(t_tree *tree); // || and && handling roi 0621
int			is_word_root(t_tree *tree);
int			is_special_root(t_tree *tree);
int			is_only_asterisks(char *str);

/* execute_export_utils.c */
// /* static  */int			handle_no_equal_sign(t_data *data, char *arg);
// /* static */ int			handle_equal_sign(t_data *data, char *arg);
// int			has_equal_sign(char *str);
int			process_export_args(t_data *data, t_tree *tree);

/* sorted_envir.c */
t_envir		*copy_envir_list(t_envir *original);
void		swap_nodes(t_envir *a, t_envir *b);
// static void	sort_envir_list(t_envir *list);
t_envir		*copy_and_sort_envir_list(t_envir *original);
// void		fill_envp(char **envp, t_envir **lst); // roi 0623 double declaration

/* envirlists_utils.c */
void		ft_envadd_back(t_envir **lst, t_envir *new);
void		ft_envadd_front(t_envir **lst, t_envir *new);
void		ft_envclear(t_envir **lst);
void		ft_envdelone(t_envir *lst, void (*del));

/* split_parenth.c */
// char		**split_parenth(char const *s, char c);
char		**split_parenth(char *s, char c);

/* tracing.c   */
void		out_t_envir(char *comment, t_envir *env_list);
void		out_t_tree(char *comment, t_tree *tree);
void		tree_out(t_tree *tree);
void		out_t_data_data(char *comment, t_data *data);
void		out_oochar(char *comment, char **temp);


/* execute_pipe_utils.c */
void		create_pipe_and_check(int pipe_fd[2]);
void		close_pipe(int pipe_fd[2]);

/* commands.c */
void		free_paths(char **paths, char **original_paths);
char		*find_executable_path(t_data *data, char *cmd);
t_envir		*find_envir_variable(t_data *data, char *var_name, int len);

/* execute_word_utils.c */
pid_t		create_child_process(char **exec_path);
void		redirect_fds(int fd_inp, int fd_out);
void		execute_forked_command(t_data *data, t_tree *tree, char *exec_path);
int			handle_exit_status(t_data *data, pid_t pid, int status, \
char **exec_path);
int			fork_command(t_command_args *args);

extern pid_t	g_child_pid; //Store process ID

#endif
