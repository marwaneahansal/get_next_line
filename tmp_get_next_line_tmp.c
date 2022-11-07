/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 08:09:25 by mahansal          #+#    #+#             */
/*   Updated: 2022/11/07 08:23:53 by mahansal         ###   ########.fr       */
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

int	read_file(char *buffer, char *rest, int fd)
{
	int readed;	

	readed = 0;
	while (readed > 0 && check_buffer_line(buffer))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			return (0);
		}
		else if (readed > 0)
		{
			
		}
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
		
	if (fd < 0)
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	read_file(buffer, rest, fd);
}
	