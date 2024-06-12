/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:01:10 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/09 13:41:02 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->token_list)
		free_tokens(&data->token_list, free);
	if (data->input_line)
		ft_memdel(&data->input_line);
	if (data->root_directory && *data->root_directory)
		free_2darray(data->root_directory);
	free(data);
	data = NULL;
}

void	free_tokens(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_memdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}
