/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 22:07:22 by rriyas            #+#    #+#             */
/*   Updated: 2021/10/23 17:50:18 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_saved(char **saved)
{
	if (!*saved)
		return ;
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

void	parse_buffer_string(char **saved, char **buff, char **line, long *pos)
{
	char	*temp;

	*pos = ft_strchr(*buff, '\n');
	if (*pos != -1)
	{
		if (!*line)
			*line = sbstr(*buff, 0, *pos + 1);
		else
		{
			temp = sbstr(*buff, 0, *pos + 1);
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
	save_leftovers(&(*saved), &(*buff), *pos);
}

char	*get_next_line(int fd)
{
	static char		*saved[1024];
	char			*line;
	char			*buff;
	long			rd;
	long			pos;

	line = NULL;
	if (fd < 0 || fd > 1023)
		return (line);
	buff = malloc(BUFFER_SIZE + 1);
	parse_saved_string(&saved[fd], &line, &pos);
	if (!line || ft_strchr(line, '\n') == -1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		pos = -1;
		while (rd > 0 && pos == -1)
		{
			buff[rd] = 0;
			parse_buffer_string(&saved[fd], &buff, &line, &pos);
			if (pos == -1)
				rd = read(fd, buff, BUFFER_SIZE);
		}
	}
	free(buff);
	return (line);
}
