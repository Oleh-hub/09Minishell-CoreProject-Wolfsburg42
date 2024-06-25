/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:40:57 by beredjhe          #+#    #+#             */
/*   Updated: 2024/06/24 10:49:15 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* counts the number of arguments,
considering quoted strings as single arguments*/
int	ft_countarr_args(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c && !in_quotes(s, i + 1))
				|| s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

/*splits the command string into an array of arguments,
handling memory allocation and copying of substrings.*/
int	ft_arrarr_args(char **arr, char *s, char c, int str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == c && !in_quotes(s, j))
			i = j + 1;
		if (s[j] != c && ((s[j + 1] == c && !in_quotes(s, j + 1)) || !s[j + 1]))
		{
			arr[str] = ft_calloc((j - i + 2), sizeof(char));
			if (!arr[str])
			{
				while (str--)
					free(arr[str]);
				return (0);
			}
			ft_strlcpy(arr[str], s + i, j - i + 2);
			str++;
		}
		j++;
	}
	arr[str] = NULL;
	return (1);
}

/*splits a string s into an array of strings based on a delimiter c,
while handling quoted substrings correctly.*/
char	**ft_split_args(char *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = ft_calloc((ft_countarr_args(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_arrarr_args(arr, s, c, 0))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
