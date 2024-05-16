/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:37:16 by welee             #+#    #+#             */
/*   Updated: 2024/05/16 19:48:22 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line.c
 * @brief Read a line from a file descriptor
 */

#include "get_next_line.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static char	*extract_concatenated_line(t_list **remainder)
{
	t_list	*temp;
	size_t	len;
	char	*line;

	temp = *remainder;
	len = 0;
	while (temp)
	{
		len += strlen(temp->content);
		temp = temp->next;
	}
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	temp = *remainder;
	while (temp)
	{
		strcat(line, temp->content);
		temp = temp->next;
	}
	return (line);
}

static char	*find_and_split_newline(char *line,
	t_list **remainder, char **buffer)
{
	char	*newline_pos;
	t_list	*temp;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		*buffer = ft_strdup(newline_pos + 1);
	}
	while (*remainder)
	{
		temp = (*remainder)->next;
		free((*remainder)->content);
		free(*remainder);
		*remainder = temp;
	}
	if (*buffer)
		ft_lstadd_back(remainder, ft_lstnew(*buffer));
	return (line);
}

static char	*extract_line(t_list **remainder, char **buffer)
{
	char	*line;

	if (!(*remainder) && !(*buffer))
		return (NULL);
	if (*buffer)
	{
		ft_lstadd_back(remainder, ft_lstnew(*buffer));
		*buffer = NULL;
	}
	line = extract_concatenated_line(remainder);
	if (!line)
		return (NULL);
	line = find_and_split_newline(line, remainder, buffer);
	return (line);
}

static int	read_and_store(int fd, t_list **remainder, char **buffer)
{
	int	bytes_read;

	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		(*buffer)[bytes_read] = '\0';
		if (ft_strchr(*buffer, '\n'))
			return (bytes_read);
		ft_lstadd_back(remainder, ft_lstnew(ft_strdup(*buffer)));
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
	}
	return (free(*buffer), *buffer = NULL, bytes_read);
}

char	*get_next_line(int fd)
{
	static t_list	*remainder;
	char			*buffer;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_and_store(fd, &remainder, &buffer);
	if (bytes_read < 0)
		return (NULL);
	return (extract_line(&remainder, &buffer));
}
