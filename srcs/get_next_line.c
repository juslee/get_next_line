/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/05/03 15:54:28 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

/**
 * @brief This function reads a file and returns the next line from the file
 * descriptor.
 * @param fd File descriptor
 * @return The next line from the file descriptor
 */
char	*get_next_line(int fd)
{
	static char	*line;
	char		*buf;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buf))
		return (NULL);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		line = ft_strjoin(line, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (line);
}
