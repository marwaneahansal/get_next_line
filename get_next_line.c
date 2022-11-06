/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:53:40 by mahansal          #+#    #+#             */
/*   Updated: 2022/11/06 06:43:29 by mahansal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		index++;
	}
	line = malloc((index + 2) * sizeof(char));
	if (!line)
		return (0);
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		line[index] = buffer[index];
		index++;
	}
	line[index] = '\n';
	line[index++] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			readed;
	char		*buffer;
	char		*line;
	static char	*rest;

	if (fd < 0)
		return (0);
	readed = 1;
	line = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	while (readed > 0 && check_buffer_line(buffer) != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			return (0);
		}
		else if (readed > 0)
		{
			rest = ft_strjoin(rest, buffer);
			if (!check_buffer_line(rest))
				break;
		}
	}
	printf("\n*********\n");
	printf("----   rest  ----\n%s", rest);
	printf("\n---- end rest ----\n");
	printf("\n*********\n");
	if (rest)
	{
		line = fill_line(rest);
	}
	return (line);
}

int	main()
{
	int fd = open("test_file.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("\n```````````````\n");
	printf("----   line  ----\n%s", line);
	printf("---- end line ----\n```````````````\n");
}
