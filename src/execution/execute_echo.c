/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:18:46 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 11:35:29 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0612
	'echo -nnnnnnnnnn JKL'
	checks the first argument of char **args that might be an '-n' /'-nnnn' 
	option of command echo
 */
static int	echo_handle_option(char **args)
{
	int	i;

	i = 0;
	if (args[1] && args[1][i] == '-')
	{
		i++;
		while (args[1][i] == 'n')
			i++;
		if (args[1][i] == '\0')
			return (1);
	}
	return (0);
}

/* 
	roi 0704
	prints the string argument arg int fd_out
	RETURN: always 0
	Refucturing. Created becasue of 25 lines norminette rule.
*/
static int	prn_out(char *arg, int fd_out, int first_arg_printed)
{
	if (first_arg_printed)
		ft_putstr_fd(" ", fd_out);
	ft_putstr_fd(arg, fd_out);
	return (0);
}

/* 
	roi 0612-0704
	if there is not opion '-n' -> no_newline = 0 and 
	 '\n' after the last argument is being printed
	all arguments are printed out with a space between them
	roi 0704
	muliple -n flags before argument are ignored like in bash,
	cases like 'echo -n -n JKL -n'
 */
	// i = 1 + no_newline - 1;
int	execute_echo(char *args[], int fd_out)
{
	int		no_newline;
	int		i;
	int		first_arg_printed;

	first_arg_printed = 0;
	no_newline = echo_handle_option(args);
	i = 1 + no_newline;
	while (args[i])
	{
		if (!strcmp (args[i], "-n") && !first_arg_printed)
		{
			i++;
			continue ;
		}
		if (args[i][0] != '\0')
			first_arg_printed = 1 + prn_out(args[i], fd_out, first_arg_printed);
		i++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
