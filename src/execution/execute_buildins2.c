/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:13:44 by oruban            #+#    #+#             */
/*   Updated: 2024/07/04 13:22:51 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	roi0610
	if the directory was changed 0 if not 1 with error message "pwd" is returned
 */
int	execute_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd), 0);
	else
		return (perror("pwd"), data->exit_status = 1);
}

/*
roi 0610
Executs buiildin command 'exit' and sets data->exit_status;
exit with sting argument causes error message and exit code 2.
freeng data memallocacion b4 exiting grarantees link nodes 2 b freed as well.
*/
void	execute_exit(t_data *data, t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->args_array[1])
	{
		if (!is_number(tree->args_array[1]))
		{
			data->exit_status = 2;
			printf("exit\nminishell: exit: %s: numeric argument required\n", \
			tree->args_array[1]);
		}
		else
		{
			i = ft_atoi(tree->args_array[1]);
			data->exit_status = i;
			exit_shell("exit", i, data);
		}
	}
	else
		exit_shell("exit", 0, data);
	free_data(data);
	exit(2);
}

/* 
roi 0611
just an intermidiate function made to create a buitfull standard name
for as for all bildin functions : execute_COMMANDNAME()
 */
void	execute_env(t_envir **env, int fd_out)
{
	ft_enviter(*env, fd_out, print_env_node);
}
