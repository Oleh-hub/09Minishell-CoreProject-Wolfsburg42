/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:30:58 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 21:39:10 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_quotes(char **str, t_data *data)
{
	char	*temp;

	temp = NULL;
	while (*str)
	{
		if (has_quotes(*str) || has_dollar(*str))
		{
			temp = expand_quotes(data, *str);
			if (!temp)
				return ;
			ft_memdel(&(*str));
			*str = ft_strdup(temp);
			ft_memdel(&temp);
		}
		str++;
	}
}

int	has_unclosed_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (last_opened == 0)
				last_opened = *str;
			else if (last_opened == *str)
				last_opened = 0;
		}
		str++;
	}
	if (last_opened != 0)
	{
		ft_putstr_fd("Close the quote!\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/*Check_d_quote is used to find a closing double quote
in a string starting from a given position and to determine if a
specified position lies within those double quotes. The function
updates the index *i to the position of the closing double quote
(or end of the string) and returns an indicator of whether the
position is within the quotes or if a closing quote was found.*/
int	check_d_quote(char *s, int *i, int pos)
{
	int	double_q;
	int	j;

	j = *i + 1;
	double_q = 1;
	while (s[j])
	{
		if (s[j] == '\"')
		{
			double_q = 0;
			if (pos > *i && pos < j)
				return (2);
			else
				break ;
		}
		else
			j++;
	}
	*i = j;
	return (double_q);
}

int	check_s_quote(char *s, int *i, int pos)
{
	int	single_q;
	int	j;

	j = *i + 1;
	single_q = 1;
	while (s[j])
	{
		if (s[j] == '\'')
		{
			single_q = 0;
			if (pos > *i && pos < j)
				return (1);
			else
				break ;
		}
		else
			j++;
	}
	*i = j;
	return (single_q);
}

/*Checks if a specific position in a string is within a quoted section*/
int	in_quotes(char *s, int pos)
{
	int	i;
	int	result;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (s[i] == '\"')
			{
				result = check_d_quote(s, &i, pos);
				if (result != 0)
					return (result);
			}
			else if (s[i] == '\'')
			{
				result = check_s_quote(s, &i, pos);
				if (result != 0)
					return (result);
			}
		}
		i++;
	}
	return (0);
}
