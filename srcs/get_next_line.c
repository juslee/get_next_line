/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/06/07 10:09:28 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief Read a line from a file descriptor
 */

#include "get_next_line.h"

static void	ft_free_ptr(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*update_remainder(char **remainder, char *newline)
{
	char	*line;
	char	*temp;

	*newline = '\0';
	line = ft_strdup(*remainder);
	temp = ft_strdup(newline + 1);
	ft_free_ptr(remainder);
	*remainder = temp;
	return (line);
}

static char	*read_line(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*newline;
	char	*temp;
	ssize_t	bytes_read;

	newline = ft_strchr(*remainder, '\n');
	while (!(newline))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*remainder, buffer);
		ft_free_ptr(remainder);
		*remainder = temp;
	}
	if (!*remainder)
		return (NULL);
	if (newline)
		return (update_remainder(remainder, newline));
	else
		return (ft_strdup(*remainder));
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, &remainder);
	if (!line || !*line)
	{
		ft_free_ptr(&line);
		return (NULL);
	}
	return (line);
}
