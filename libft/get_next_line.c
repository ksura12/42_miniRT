/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaheinz <kaheinz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:23:53 by kaheinz           #+#    #+#             */
/*   Updated: 2022/05/29 02:02:29 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd > 1024 || read(fd, NULL, 0) || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buffer[0] != '\0')
		line = stringjoin(line, buffer);
	line = reading_from_fd(buffer, line, fd);
	if (!line)
		return (NULL);
	substr_after_newline(line, &buffer[0]);
	line = substr_before_newline(line);
	return (line);
}

char	*reading_from_fd(char *buffer, char *line, int fd)
{
	int		reading;

	reading = BUFFER_SIZE;
	while (!finding_newline(buffer) && reading == BUFFER_SIZE)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading == -1 || (reading == 0 && buffer[0] == '\0'))
		{
			free(line);
			return (NULL);
		}	
		buffer[reading] = '\0';
		line = stringjoin(line, buffer);
	}
	return (line);
}

char	*substr_before_newline(char *line)
{
	char	*substring;
	size_t	i;
	size_t	newline;

	i = 0;
	newline = 0;
	while (line[newline] != '\0' && line[newline] != '\n')
		newline++;
	substring = malloc(newline + 2);
	if (!line || !substring)
	{
		free(substring);
		return (NULL);
	}
	while (i <= newline)
	{
		substring[i] = line[i];
		i++;
	}
	substring[i] = '\0';
	free(line);
	return (substring);
}

void	substr_after_newline(char *line, char *buffer)
{
	size_t	i;
	size_t	newline;
	size_t	len;
	size_t	buflen;

	i = 0;
	buflen = ftt_strlen(buffer);
	newline = 0;
	len = ftt_strlen(line);
	while (line[newline] != '\0' && line[newline] != '\n')
		newline++;
	newline++;
	if (!line || !buffer)
		return (free(buffer));
	while (newline <= len)
	{
		buffer[i] = line[newline];
		newline++;
		i++;
	}
	while (i <= buflen)
		buffer[i++] = '\0';
}
