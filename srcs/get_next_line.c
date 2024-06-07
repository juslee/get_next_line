/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/06/07 15:29:36 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief Read a line from a file descriptor
 */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

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
	while (!ft_strchr(stored, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(stored);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = stored;
		stored = ft_strjoin(temp, buffer);
		if (!stored)
		{
			free(temp);
			return (NULL);
		}
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
 * @brief Save the remaining text after the extracted line.
 *
 * @param stored Previously read but not yet processed text.
 * @return char* Newly allocated string containing the remaining
 * text, NULL if no remaining text is found.
 */
static char	*save_remaining(char *stored)
{
	size_t	i;
	char	*remaining;

	if (!stored || stored[0] == '\0')
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
		return (NULL);
	remaining = ft_substr(stored, i + 1, ft_strlen(stored) - i - 1);
	return (remaining);
}

/**
 * @brief Get the next line from a file descriptor.
 *
 * @param fd File descriptor to read from.
 * @return char* Newly allocated string containing the next line,
 * NULL if an error occurs or no more lines are found.
 */
char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = read_to_newline(fd, stored);
	if (!stored)
		return (NULL);
	line = extract_line(stored);
	if (!line)
	{
		free(stored);
		stored = NULL;
		return (NULL);
	}
	temp = stored;
	stored = save_remaining(temp);
	free(temp);
	return (line);
}
