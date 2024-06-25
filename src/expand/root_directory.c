/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beredzhe <beredzhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:04:28 by beredzhe          #+#    #+#             */
/*   Updated: 2024/06/24 21:17:21 by beredzhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*read the contents of a directory into memory for for further processing*/
char	**read_directory(DIR *d, char **root_directory)
{
	struct dirent	*dir;
	int				i;

	i = 0;
	dir = readdir(d);
	while (dir != NULL)
	{
		if (ft_strncmp(dir->d_name, ".", 1))
		{
			root_directory[i] = ft_strdup(dir->d_name);
			if (root_directory[i] == NULL)
			{
				while (i > 0)
					ft_memdel(&root_directory[--i]);
				free(root_directory);
				closedir(d);
				return (NULL);
			}
			i++;
		}
		dir = readdir(d);
	}
	root_directory[i] = NULL;
	closedir(d);
	return (root_directory);
}

/*retrieve and return the list of directory entries*/
char	**get_root_directory(void)
{
	DIR				*d;
	int				len;
	char			**root_directory;

	len = count_root_directory();
	root_directory = malloc(sizeof(char *) * (len + 1));
	if (root_directory == NULL)
		return (NULL);
	d = opendir(".");
	if (d)
	{
		root_directory = read_directory(d, root_directory);
		if (root_directory == NULL)
			return (NULL);
	}
	sort_directory(root_directory);
	return (root_directory);
}

/*sorting in alphabetical order using bubble sort*/
void	sort_directory(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*counts the number of entries in the root directory*/
int	count_root_directory(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	count = 0;
	d = opendir("/");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				count++;
			dir = readdir(d);
		}
		closedir(d);
	}
	return (count);
}
