/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:41:58 by welee             #+#    #+#             */
/*   Updated: 2024/06/10 15:07:07 by welee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	*line;
	char	*line2;

	if (argc != 3)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open(argv[2], O_RDONLY);
	if (fd2 == -1)
		return (1);
	line = get_next_line(fd);
	line2 = get_next_line(fd2);
	while (line && line2)
	{
		printf("%s", line);
		printf("%s", line2);
		free(line);
		free(line2);
		line = get_next_line(fd);
		line2 = get_next_line(fd2);
	}
	close(fd);
	return (0);
}
