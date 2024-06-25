/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:15:17 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/25 10:23:14 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*updates the 'word' by concatenating all strings
in the 'root directory' from a 't_data' structure*/
void	update_asterisk_token(t_token *token, t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	ft_memdel(&token->word);
	while (data->root_directory[i])
	{
		if (!token->word)
			token->word = ft_strjoin("", data->root_directory[i]);
		else
		{
			temp = ft_strjoin(token->word, data->root_directory[i]);
			ft_memdel(&token->word);
			token->word = temp;
		}
		temp = ft_strjoin(token->word, " ");
		ft_memdel(&token->word);
		token->word = temp;
		i++;
	}
}

void	extend_asterisk(t_token *token, t_data *data)
{
	if (is_only_asterisks(token->word))
		update_asterisk_token(token, data);
	else if (has_asterisk(token->word))
		check_matches(token, data->root_directory);
}

/*handle wildcard matching*/
int	match_pattern(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *string == '\0')
		return (0);
	if (*pattern == *string)
		return (match_pattern(pattern + 1, string + 1));
	if (*pattern == '*')
		return (match_pattern(pattern + 1, string)
			|| match_pattern(pattern, string + 1));
	return (0);
}
