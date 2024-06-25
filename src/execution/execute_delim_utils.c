
#include "minishell.h"

void	add_heredoc_file(t_data *data, char *filename, int id)
{
	t_heredoc_file	*new_file;

	new_file = malloc(sizeof(t_heredoc_file));
	new_file->filename = ft_strdup(filename);
	new_file->id = id;
	new_file->next = data->heredoc_file;
	data->heredoc_file = new_file;
}

void	free_heredoc_info(t_heredoc_info *info)
{
	if (info->filename)
		ft_strdel(&info->filename);
	if (info->limiter)
		ft_strdel(&info->limiter);
	if (info->token)
		ft_strdel(&info->token);
}
