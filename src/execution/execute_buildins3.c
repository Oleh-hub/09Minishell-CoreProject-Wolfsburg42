/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildins3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:12:39 by oruban            #+#    #+#             */
/*   Updated: 2024/06/12 07:23:34 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* roi 0606:
checking if PATH Is vailid name of an accesible directory 
	1. case 'cd PATH' if there is No such file or directory checked with stat()
	2. case 'cd PATH' if PATH is not a directory checked with S_IFDIR
if PATH is Ok chdir() to PATH
*/
static int	validate_and_change_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat))
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	if ((path_stat.st_mode & S_IFMT) != S_IFDIR)
		return (printf("minishell: cd: %s: Not a directory\n", path), 1);
	if (chdir(path) != 0)
	{
		printf("it's a file: %s: ", path);
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

/* roi 0607
1. the memory to allocate for cwd is defined by PATH_MAX form limits.h
	in my case PATH_MAX = 4096 
2. if an error happens during maloc() -> print message + txt of error (perror)
3. it mem is allocated -> we get the name of curretnt working directory 
	int cwd by getcwd() function
4. if getcwd() fails -> free mem and return NULL
*/
static	int	update_pwd(t_data *data)
{
	char	*cwd;
	t_envir	*pwd_env;

	cwd = malloc(PATH_MAX);
	if (!cwd)
		return (perror("minishell: cd: Cant get the current directory\n"), 1);
	if (!getcwd(cwd, PATH_MAX))
		return (free(cwd), 1);
	// cwd = get_curr_dir();
	if (!cwd)
		return (printf("minishell: error getting current directory\n"), 1);
	pwd_env = find_envir_variable(data, "PWD", 3);
	if (!pwd_env)
		return (free(cwd), 0);
	//============
	if (pwd_env->var_value)
	{
		free(pwd_env->var_value);
		pwd_env->var_value = NULL;
	}
	// ft_strdel(&pwd_env->var_value); 
	pwd_env->var_value = ft_strdup(cwd);
	return (free(cwd), 0);
}

/* roi 0606:
1. - 'cd' command without argumants implemented (go to $HOME), 
2. - otherwise - change into argument validate_and_change_directory() 
3/ - and update_pwd()
*/
int	execute_cd(t_data *data, char *path)
{
	// out_t_envir("inside execute_cd()", data->env_list); // roi 0607
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), 1);
	}
	if (validate_and_change_directory(path))
		return (1);
	return (update_pwd(data));
}