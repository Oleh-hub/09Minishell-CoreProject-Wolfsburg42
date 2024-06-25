/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:46:20 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 11:00:07 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*handlers for SIGINT, SIGTSTP, and SIGQUIT signals.*/
void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_c;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
				g_child_pid++;
			}
			else
			{
				rl_on_new_line();
				rl_redisplay();
			}
		}
		else
			exit(EXIT_SUCCESS);
	}
}

/*handle CTRL+Z and CTRL+\*/
void	handle_sigtstp_sigquit(int signo)
{
	if (signo == SIGTSTP || signo == SIGQUIT)
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
	handle_sigtstp_sigquit(signo);
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
		rl_on_new_line();
		rl_redisplay();
		exit_shell("exit", 0, data);
	}
	if (ft_strlen(input) == 0)
	{
		ft_memdel(&input);
		return (1);
	}
	return (0);
}
