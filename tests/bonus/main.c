/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:41:58 by welee             #+#    #+#             */
/*   Updated: 2024/06/10 17:28:38 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd, fd2, fd3;
	char	*line, *line2, *line3;

	if (argc != 4)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open(argv[2], O_RDONLY);
	if (fd2 == -1)
		return (1);
	fd3 = open(argv[3], O_RDONLY);
	if (fd3 == -1)
		return (1);

	line = get_next_line(fd);
	printf("fd1: %s", line);
	fflush(stdout);
	free(line);
	line2 = get_next_line(fd2);
	printf("fd2: %s", line2);
	fflush(stdout);
	free(line2);
	line3 = get_next_line(fd3);
	printf("fd3: %s", line3);
	fflush(stdout);
	free(line3);

	line = get_next_line(fd);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	printf("fd1: %s", line);
	fflush(stdout);
	printf("fd2: %s", line2);
	fflush(stdout);
	printf("fd3: %s", line3);
	fflush(stdout);
	free(line);
	free(line2);
	free(line3);

	line = get_next_line(fd);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	printf("fd1: %s", line);
	fflush(stdout);
	printf("fd2: %s", line2);
	fflush(stdout);
	printf("fd3: %s", line3);
	fflush(stdout);
	free(line);
	free(line2);
	free(line3);

	line = get_next_line(fd);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	printf("fd1: %s", line);
	fflush(stdout);
	printf("fd2: %s", line2);
	fflush(stdout);
	printf("fd3: %s", line3);
	fflush(stdout);
	free(line);
	free(line2);
	free(line3);

	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
