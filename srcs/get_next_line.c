/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/09/20 00:34:53 by welee            ###   ########.fr       */
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
#include <stdio.h>

/**
 * @brief Read from a file descriptor until a newline is encountered.
 *
 * @param fd File descriptor to read from.
 * @param stored Previously read but not yet processed text.
 * @return char* Newly allocated string containing the read text,
 * NULL on error.
 */
static char	*read_to_newline(int fd, char stored[10240])
{
	char	*buffer;
	int		bytes_read;
	size_t	stored_len;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stored, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		stored_len = ft_strlen(stored);
		if (stored_len + bytes_read >= 10240)
			return (free(buffer), NULL);
		ft_strcat(stored, buffer);
	}
	return (free(buffer), stored);
}

/**
 * @brief Extract a line from the stored text.
 *
 * @param stored Previously read but not yet processed text.
 * @return char* Newly allocated string containing the extracted line,
 * NULL if no line is found.
 */
static char	*extract_line(char stored[10240])
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
static void	save_remaining(char stored[10240])
{
	size_t	i;
	size_t	j;

	if (!stored || stored[0] == '\0')
		return ;
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		stored[0] = '\0';
		return ;
	}
	i++;
	j = 0;
	while (stored[i])
	{
		stored[j] = stored[i];
		i++;
		j++;
	}
	stored[j] = '\0';
	return ;
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
	static char	stored[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_newline(fd, stored))
		return (NULL);
	line = extract_line(stored);
	if (line == NULL)
		return (NULL);
	save_remaining(stored);
	return (line);
}
