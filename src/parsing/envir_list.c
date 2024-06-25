/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:53:30 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 10:57:17 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	find_equal_sign(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

/*parsing a single environment variable string in the
format 'KEY=VALUE' and storing the key and value in a
't_envir' structure.*/
void	extract_env_var(t_envir *envir, char *env)
{
	unsigned int	i;
	size_t			len;

	i = find_equal_sign(env);
	len = ft_strlen(env);
	envir->var_name = ft_substr(env, 0, i);
	envir->var_value = ft_substr(env, i + 1, len - i);
}

/*create a linked list of environment variables from an
array of environment strings*/
t_envir	*fill_env(char **env, t_data *data)
{
	t_envir			*envir;
	t_envir			*head;

	if (!*env)
		return (NULL);
	envir = ft_envnew();
	head = envir;
	while (*env)
	{
		extract_env_var(envir, *env);
		env++;
		if (*env)
		{
			envir->next = ft_envnew();
			envir->next->prev = envir;
			envir = envir->next;
		}
	}
	data->env_list = head;
	return (head);
}
