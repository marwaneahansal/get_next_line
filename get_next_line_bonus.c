/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:53:40 by mahansal          #+#    #+#             */
/*   Updated: 2022/11/12 02:23:58 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_buffer_line(char *buffer)
{
	int	index;

	index = 0;
	while (buffer[index])
	{
		if (buffer[index] == '\n')
			return (0);
		index++;
	}
	return (1);
}

char	*fill_line(char *buffer)
{
	int		index;
	char	*line;
	int		add_line;

	index = 0;
	add_line = 0;
	if (buffer[index] == '\0')
		return (0);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (buffer[index] && buffer[index] == '\n')
		add_line = 1;
	line = malloc((index + add_line + 1) * sizeof(char));
	if (!line)
		return (0);
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		line[index] = buffer[index];
		index++;
	}
	if (add_line)
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*reset_rest(char *rest)
{
	int		rest_len;
	int		index;
	char	*tmp;

	index = 0;
	rest_len = 0;
	while (rest[index] && rest[index] != '\n')
		index++;
	if (rest[index] == '\n')
		index++;
	if (rest[index] == '\0')
	{
		free(rest);
		return (0);
	}
	rest_len = ft_strlen(&rest[index]);
	tmp = ft_strdup(&rest[index]);
	free(rest);
	if (!tmp)
		return (0);
	return (tmp);
}

int	read_file(int fd, char **rest, char *buffer)
{
	int		readed;

	readed = 1;
	while (readed > 0 && check_buffer_line(buffer))
	{
		buffer[0] = '\0';
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			clear_rest(*rest);
			return (0);
		}
		else if (readed >= 0)
		{
			if (readed > 0)
				buffer[readed] = '\0';
			*rest = ft_strjoin(*rest, buffer);
			if (!(*rest))
				return (0);
			if (readed > 0 && !check_buffer_line(*rest))
				break ;
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	int			readed;
	char		*buffer;
	char		*line;
	static char	*rest[OPEN_MAX];

	if (fd < 0)
		return (0);
	readed = 1;
	line = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	if (!read_file(fd, &rest[fd], buffer))
		return (0);
	free(buffer);
	if (rest[fd])
	{
		line = fill_line(rest[fd]);
		rest[fd] = reset_rest(rest[fd]);
	}
	return (line);
}
