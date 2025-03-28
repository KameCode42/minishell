/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dle-fur <dle-fur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:46:35 by dle-fur           #+#    #+#             */
/*   Updated: 2024/11/07 17:47:07 by dle-fur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	nbyte;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		return (NULL);
	}
	while (!ft_strchr(line, '\n'))
	{
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte == 0)
			break ;
		if (nbyte == -1)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		buffer[nbyte] = '\0';
		line = ft_line_join(line, buffer);
	}
	free(buffer);
	return (line);
}

static char	*next_line(char	*line)
{
	char	*next_char;
	char	*new_line;

	next_char = ft_strchr(line, '\n');
	if (next_char == NULL)
	{
		return (NULL);
	}
	next_char++;
	new_line = ft_strdup(next_char);
	*next_char = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*new_line;
	char		*line;

	line = read_line(fd, new_line);
	new_line = next_line(line);
	return (line);
}
