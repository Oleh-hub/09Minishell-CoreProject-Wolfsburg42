/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:18:50 by oruban            #+#    #+#             */
/*   Updated: 2024/06/19 19:15:07 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0612-14
	output all the environment variables in sorted order
	'export' command is executed with the following steps:
	1. if command 'export' has arguments like 'export OLH=1 SRG=2' -> 
		process_export_args()
	2. otherwise -> if 'export'is not followed by any arguments: 
		- copy_and_sort_envir_list() bubble sort the list of environment
		variables and return as 't_tenvir sorted'
		- and iterate the node print in fromat 'VARIABLE=Value' by 
		'ft_enviter(sorted, fd_out, print_env_node_sorted)'
		-  clear (delete the temporary list 't_envir sorted' freeing the
		memory) the temporary list 'ft_envclear(&sorted)'
		if 'export' withour arguments id being run next time - create sorted
		again but not rubbish the memory for seldom called command
 */
// out_t_tree("===>execute_export",tree); // tracing
int	execute_export(t_data *data, t_tree *tree, int fd_out)
{
	t_envir	*sorted;

	if (tree->args_array[1])
		return (process_export_args(data, tree));
	else
	{
		// out_t_envir("==>execute_export==b4copy_and_sort_envir_list\n ", data->env_list); // tracing
		sorted = copy_and_sort_envir_list(data->env_list);
		// out_t_envir("==>execute_export==AFTER copy_and_sort_envir_list\n ", sorted); // tracing
		ft_enviter(sorted, fd_out, print_env_node_sorted);
		return (ft_envclear(&sorted), 0);
	}
}

void	handle_existing_variable(t_envir *temp, char *var_value)
{
	ft_strdel(&temp->var_value);
	temp->var_value = ft_strdup(var_value);
	if (temp->visible == 1)
		temp->visible = 0;
}

void	handle_visible_variable(t_envir *temp)
{
	if (temp->visible == 0)
		temp->visible = 1;
	ft_strdel(&temp->var_value);
	temp->var_value = ft_strdup("");
}

/* 
	roi 0619
	could be static but becouse of the leath declaring line passed not 
	to norminette 
	it makes following:
	1. calls ft_envnew() - allocates memory and initiates all the fields
		of the new node with 0/NULL
	2. calles ft_strdup() to allocate memory and copy the var_name to the 
		new node field var_name
	3. if var_value is "visible" (newly created )-> set visible to 1 and 
		var_value to "" and 
		adds the new node of the variable to the end of the list
	NOTE:
		visibility is the quality being seen by both env and export 
		commands if 0 only export shos it
*/
void	handle_new_variable(t_envir **env_list, char *var_name, char *var_value)
{
	t_envir	*new_envir;

	new_envir = ft_envnew(); 
	new_envir->var_name = ft_strdup(var_name);
	if (!ft_strcmp(var_value, "visible")) 
	{
		new_envir->visible = 1;
		new_envir->var_value = ft_strdup("");
		ft_envadd_back(env_list, new_envir);
	}
	else
	{	// if the variable is not visible: roi
		new_envir->var_value = ft_strdup(var_value);
		ft_envadd_back(env_list, new_envir);
		new_envir->visible = 0;
	}
}

/* 
	roi 0619
	exexution of 'export' command with the following steps:
	Parameters are:
		1 env_list: list of environment variables
		2 var_name: name of the environment variable given as argument:
		 'export var_name' to be exported
		3 var_value: value of the environment variable 
		 'export var_name=var_value' to be exported:
		 - "visible" in case when there is no value (no '=' like 'export olh')
		4 data: data structure that has 't_envir	*env_list' having this 
		parameter is exccesive but shortens the code of the under function
		(can also be done by introduction a variable int the under function)
 */
void	export(t_envir **env_list, char *var_name, char *var_value, \
	t_data *data)
{
	t_envir	*temp;

	temp = find_envir_variable(data, var_name, ft_strlen(var_name));
	if (temp && ft_strcmp(var_value, "visible"))
		handle_existing_variable(temp, var_value);
	else if (temp && !ft_strcmp(var_value, "visible"))
		handle_visible_variable(temp);
	else if (!temp)
		handle_new_variable(env_list, var_name, var_value);
}
