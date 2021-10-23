/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:55:02 by rriyas            #+#    #+#             */
/*   Updated: 2021/10/22 00:31:47 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_saved(char **saved)
{
	if (*saved && ft_len(*saved) == 0)
	{
		free(*saved);
		*saved = NULL;
	}
}

void	save_leftovers(char **saved, char **buff, long pos)
{
	if (pos != -1 && pos + 1 < ft_len(*buff))
	{
		if (!*saved)
			*saved = ft_strdup(&(*buff)[pos + 1]);
		else
			*saved = ft_strjoin(*saved, &(*buff)[pos + 1]);
	}
}

void	parse_saved_string(char **saved, char **line, long *pos)
{
	char	*temp;

	if (!pos)
		pos = 0;
	clear_saved(&(*saved));
	while (!(*line) && *saved && *pos != -1)
	{
		*pos = ft_strchr(*saved, '\n');
		if (*pos != -1)
		{
			*line = sbstr(*saved, 0, *pos + 1);
			temp = sbstr(*saved + *pos + 1, 0, ft_len(*saved) - *pos - 1);
			if (temp)
			{
				free(*saved);
				*saved = temp;
			}
		}
		else
		{
			*line = ft_strdup(*saved);
			free(*saved);
			*saved = NULL;
		}
	}
}

void	parse_buffer_string(char **saved, char **buff, char **line, long pos)
{
	char	*temp;

	temp = NULL;
	if (pos != -1)
	{
		if (!*line)
			*line = sbstr(*buff, 0, pos + 1);
		else
		{
			temp = sbstr(*buff, 0, pos + 1);
			*line = ft_strjoin(*line, temp);
			free(temp);
		}
	}
	else
	{
		if (!*line)
			*line = ft_strdup(*buff);
		else
			*line = ft_strjoin(*line, *buff);
	}
	save_leftovers(&(*saved), &(*buff), pos);
}

char	*get_next_line(int fd)
{
	static char		*saved;
	char			*line;
	char			*buff;
	long			rd;
	long			pos;

	line = NULL;
	buff = malloc(BUFFER_SIZE + 1);
	if (saved)
		parse_saved_string(&saved, &line, &pos);
	if (!line || ft_strchr(line, '\n') == -1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		pos = -1;
		while (rd > 0 && pos == -1)
		{
			buff[rd] = 0;
			pos = ft_strchr(buff, '\n');
			parse_buffer_string(&saved, &buff, &line, pos);
			if (pos == -1)
				rd = read(fd, buff, BUFFER_SIZE);
		}
	}
	free(buff);
	return (line);
}
