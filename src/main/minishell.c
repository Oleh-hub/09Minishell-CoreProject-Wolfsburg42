/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:25:31 by oruban            #+#    #+#             */
/*   Updated: 2024/06/25 20:35:46 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* quates expand:
echo "'"$USER">
echo "'"'$USER'"'"
echo "'""$USER""'"
echo "'""$USER""'"
echo "$USER"     _ruban
echo "$USER"_ruban
echo "$USER" _ruban
asterix expand:
ls * */

#include "minishell.h"

pid_t	g_child_pid = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_data			*data;
	char			**env;

	(void)argc;
	(void)argv;
	data = NULL;
	env = NULL;
	// printbanner(); //roi0606
	if (!*envp)
	{
		env = create_envp();
		init_data(&(data), env);
		// find the shell level and set it to 1 //roi0616
	}
	else
		init_data(&(data), envp);
	handle_signal();
	// start_loop(data);
	minishell_loop(data);
	if (env)
		free_2darray(env);
	free_data(data);
	return (0);
}

char	**create_envp(void)
{
	char	**envp;
	char	cwd[PATH_MAX];

	envp = malloc(sizeof(char *) * 4);
	if (!envp)
		exit(1);
	envp[0] = ft_strdup("SHLVL=1");
	envp[1] = ft_strdup("PATH=/bin/");
	if (getcwd(cwd, sizeof(cwd)))
		envp[2] = ft_strjoin("PWD=", cwd);
	else
	{
		ft_putstr_fd("getcwd() error\n", 2);
		free_2darray(envp);
		exit(1);
	}
	envp[3] = NULL;
	return (envp);
}
