/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/06/07 14:33:41 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief Read a line from a file descriptor
 */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/select.h>
#include "get_next_line_bonus.h"

/**
 * @brief Read from a file descriptor until a newline is encountered.
 *
 * @param fd File descriptor to read from.
 * @param stored Previously read but not yet processed text.
 * @return char* Newly allocated string containing the read text,
 * NULL on error.
 */
static char	*read_to_newline(int fd, char *stored)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (!ft_strchr(stored, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stored);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = stored;
		stored = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (stored);
}

/**
 * @brief Extract a line from the stored text.
 *
 * @param stored Previously read but not yet processed text.
 * @return char* Newly allocated string containing the extracted line,
 * NULL if no line is found.
 */
static char	*extract_line(char *stored)
{
	size_t	i;
	char	*line;

	if (!stored || stored[0] == '\0')
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		line = ft_substr(stored, 0, i + 1);
	else
		line = ft_substr(stored, 0, i);
	return (line);
}

/**
 * @brief Save the remaining text after the newline character.
 *
 * @param stored Previously read but not yet processed text.
 * @return char* The remaining text after the newline character,
 * NULL if no remaining text.
 */
static char	*save_remaining(char *stored)
{
	size_t	i;
	char	*remaining;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
		return (NULL);
	remaining = ft_substr(stored, i + 1, ft_strlen(stored) - i - 1);
	return (remaining);
}

/**
 * @brief Read a line from a file descriptor.
 *
 * @param fd File descriptor to read from.
 * @return char* Newly allocated string containing the read line,
 * NULL if an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*stored[FD_SETSIZE];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SETSIZE)
		return (NULL);
	stored[fd] = read_to_newline(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = extract_line(stored[fd]);
	if (!line)
	{
		free(stored[fd]);
		stored[fd] = NULL;
		return (NULL);
	}
	temp = stored[fd];
	stored[fd] = save_remaining(temp);
	free(temp);
	return (line);
}
