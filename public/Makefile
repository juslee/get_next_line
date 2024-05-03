# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:51:47 by welee             #+#    #+#              #
#    Updated: 2024/05/03 15:59:32 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEFINE = -D BUFFER_SIZE=32
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

all: ${NAME}

$(NAME): $(OBJS)
	${LIBC} ${NAME} ${OBJS}

%.o: %.c
	$(CC) $(CFLAGS) $(DEFINE) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all dist

.PHONY: all clean fclean re
