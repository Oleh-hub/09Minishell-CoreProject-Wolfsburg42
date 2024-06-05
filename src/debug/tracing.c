/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:22:45 by oruban            #+#    #+#             */
/*   Updated: 2024/06/04 11:46:29 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void out_t_tree(char *comment, t_tree chainlink)
{
    printf("%s\n", comment);
    printf("type: %d\n", chainlink.type);
    printf("value: %s\n", chainlink.value);
    for (int i = 0; chainlink.args_array[i]; i++)
        printf("args_array: %s\n", chainlink.args_array[i]);
}
