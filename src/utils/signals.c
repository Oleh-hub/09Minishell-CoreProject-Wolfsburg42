/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:46:20 by beredzhe          #+#    #+#             */
/*   Updated: 2024/07/06 11:45:53 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
handlers for SIGINT and SIGQUIT signals.
sa_int handles Ctrl+C
sa_quit handles with Ctrl+D
*/
void	handle_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_c;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*handle CTRL+C*/
void	handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			if (g_child_pid == 42)
				g_child_pid = 44;
			if (g_child_pid != 0 && g_child_pid != 44)
			{
				kill(g_child_pid, SIGINT);
				printf("\n");
				g_child_pid++;
			}
			else
			{
				write(STDOUT_FILENO, "\n", 1);
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
}

/*handle CTRL+\*/
void	handle_sigquit(int signo)
{
	if (signo == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
		{
			if (g_child_pid == 0)
				rl_redisplay();
			else
			{
				kill(g_child_pid, signo);
				g_child_pid += 2;
			}
		}
	}
}

void	handle_c(int signo)
{
	handle_sigint(signo);
	handle_sigquit(signo);
}

/*In summary, handle_d handles two special cases: 
when input is NULL and when input is an empty string. 
In the first case, it exits the shell. In the second case, 
it frees input and signals the caller to skip the current iteration of the loop. 
If input is a non-empty string, it signals the caller 
to proceed with the loop.*/
int	handle_d(t_data *data, char *input)
{
	if (input == NULL)
	{
		exit_shell("exit", 0, data);
	}
	if (ft_strlen(input) == 0)
	{
		ft_memdel(&input);
		return (1);
	}
	return (0);
}
