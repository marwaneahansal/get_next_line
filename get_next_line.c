/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:53:40 by mahansal          #+#    #+#             */
/*   Updated: 2022/11/07 09:25:27 by mahansal         ###   ########.fr       */
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
	int		add_line;
	
	index = 0;
	add_line = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (buffer[index] == '\n')
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
	{
		line[index] = '\n';
		index++;
	}
	line[index] = '\0';
	// line[index] = '\n';
	// line[++index] = '\0';
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
	if (rest[index] == '\0')
	{
		if (rest)
			free(rest);
		return (0);
	}
	if (rest[index] == '\n')
		index++;
	rest_len = ft_strlen(&rest[index]);
	tmp = ft_strdup(&rest[index]);
	if (rest)
		free(rest);
	if (!tmp)
		return (0);
	return (tmp);
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
	buffer[0] = '\0';
	while (readed > 0 && check_buffer_line(buffer) != 0)
	{
		buffer[0] = '\0';
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			// if (rest)
			free(rest);
			return (0);
		}
		// check if read returned 0 (the file has ended)
		else if (readed > 0)
		{
			buffer[readed] = '\0';
			rest = ft_strjoin(rest, buffer);
			if (buffer)
				free(buffer);
			if (!rest)
				return (0);
			if (!check_buffer_line(rest))
				break;
		}
	}
	if (rest)
	{
		line = fill_line(rest);
		rest = reset_rest(rest);
	}
	return (line);
}

// int	main()
// {
// 	// int fd = open("test_file.txt", O_RDONLY);
// 	int fd = open("./files/test_file.txt", O_RDONLY);
// 	printf("fd: %d\n", fd);
// 	// int fd = 3;
// 	char *line = get_next_line(fd);
// 	int	index = 1;
// 	printf("\n```````````````\n");
// 	printf("----   line %d  ----\n%s", index, line);
// 	printf("---- end line %d ----\n```````````````\n", index);
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("\n```````````````\n");
// 		printf("----   line %d  ----\n%s", index, line);
// 		printf("---- end line %d ----\n```````````````\n", index);
// 		index++;
// 	}
// }
