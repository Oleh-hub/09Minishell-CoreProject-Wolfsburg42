/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:41:00 by oruban            #+#    #+#             */
/*   Updated: 2024/07/06 13:00:04 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	roi 0614 execution 'export' command with argument (env variable) without '='
	- if there is '*' or digit in the first character of the argument -> print 
	error message and return 1.
	- otherwise -> execute export() with the variable with 'visible' value and
	return 0
	
 */
	// if (has_asterisk(arg) || ft_isdigit(arg[0]))
	// 	return (printf("minishell: export: `%s': not a valid identifier\n", \
	// 	arg), 1);
	// export(&data->env_list, arg, "visible", data);
	// return (0);
	// Iterate over each character in arg to check for invalid characters
	// Check if character is not alphanumeric and not underscore
	// If all characters are valid, execute export
static int	handle_no_equal_sign(t_data *data, char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (printf("minishell: export: `%s': \
		not a valid identifier\n", arg), 1);
	while (arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (printf("minishell: export: `%s': \
			not a valid identifier\n", arg), 1);
		i++;
	}
	export(&data->env_list, arg, "visible", data);
	return (0);
}

/* 
	roi 0614 
	handling the arguments of 'export' command that have '=' sign like 
	'export olh=1 =srg = mom' case
	// temp = ft_split_parenth(arg, '=');
	temp = ft_split(arg, '=');	// roi 0614
	export lol=lala ror=rara - done // roi 0627
 */
	// temp = ft_split(arg, '=');	// roi 0614
	// out_oochar("===>handle_equal_sign()", temp); // tracing
static int	handle_equal_sign(t_data *data, char *arg)
{
	char	**temp;
	int		result;

	temp = split_parenth(arg, '=');
	result = 0;
	if (temp[1] && !temp[2])
	{
		if (has_asterisk(temp[0]) || ft_isdigit(temp[0][0]))
			return (printf("minishell: export: `%s=%s'", temp[0], temp[1]), \
			printf(": not a valid identifier\n"), free_2darray(temp), 1);
		else
			export(&data->env_list, temp[0], temp[1], data);
	}
	else if (temp[0] && !temp[1])
	{
		if (has_asterisk(temp[0]) || ft_isdigit(temp[0][0]))
			return (printf("minishell: export: `%s': not a valid identifier\n", \
			temp[0]), free_2darray(temp), 1);
		else
			export(&data->env_list, temp[0], "", data);
	}
	free_2darray(temp);
	return (result);
}

/* 
	roi 0614
	process 'OLH=1 =SRG = MOM' that are hold in tres->args_array[1-4]
 
	checking all arguments of 'export' (like 'OLH=1' 'SRG=2') command:
	1. if there is '=' sign => handle_equal_sign()
	otherwise => handle_no_equal_sign()

	handling:
	"export olh=1 =serg = mom"case
	export lol=lala ror=rara - done
 */
		// printf("\033[34m tree->args_array[%d]		= %s\033[0m\n",
		//  i, tree->args_array[i]); // debugging
		// out_t_tree("<===process_export_args()===>export lol=lala 
		// ror=rara", tree); //tracing roi0627 
int	process_export_args(t_data *data, t_tree *tree)
{
	int		i;

	i = 0;
	while (tree->args_array[++i])
	{
		if (ft_strchr(tree->args_array[i], '='))
		{
			if (handle_equal_sign(data, tree->args_array[i]))
				return (1);
		}
		else
			if (handle_no_equal_sign(data, tree->args_array[i]))
				return (1);
	}
	return (0);
}
