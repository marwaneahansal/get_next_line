/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 06:53:40 by mahansal          #+#    #+#             */
/*   Updated: 2022/11/11 06:57:25 by mahansal         ###   ########.fr       */
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
			clear_rest(rest);
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
	static char	*rest[1024];

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

// void	printf_line(char *line, int index)
// {
// 	printf("\n```````````````\n");
// 	printf("----   line %d  ----\n%s", index, line);
// 	printf("---- end line %d  ----\n```````````````\n", index);
// }

// int main()
// {
// 	int fd = open("./files/open_close_open.txt", O_RDONLY);
// 	int fd2 = open("./files/test_file.txt", O_RDONLY);
// 	printf("fd ==> %d -- fd2 ==> %d\n", fd, fd2);
// 	int index = 1;
// 	printf_line(get_next_line(fd), index++);
// 	printf_line(get_next_line(fd2), index++);
// 	printf_line(get_next_line(fd), index++);
// 	printf_line(get_next_line(fd2), index++);
// 	printf_line(get_next_line(fd), index++);
// 	printf_line(get_next_line(fd), index++);

// }

// int	main()
// {
// 	int fd = open("./files/test_file.txt", O_RDONLY);
// 	// int fd = open("./files/empty_file.txt", O_RDONLY);
// 	printf("fd: %d\n", fd);
// 	char *line = get_next_line(fd);
// 	int	index = 1;
// 	printf("\n```````````````\n");
// 	printf("----   line %d  ----\n%s", index, line);
// 	printf("---- end line %d ----\n```````````````\n", index);
// 	while (line)
// 	{
// 		index++;
// 		line = get_next_line(fd);
// 		printf("\n```````````````\n");
// 		printf("----   line %d  ----\n%s", index, line);
// 		printf("---- end line %d ----\n```````````````\n", index);
// 	}
// }
