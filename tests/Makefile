# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 15:15:06 by welee             #+#    #+#              #
#    Updated: 2024/06/10 17:28:18 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl_test
SRCS = mandatory/main.c
BONUS_SRCS = bonus/main.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ../includes
LIBS = -L ../bin -lgnl
BONUS_LIBS = -L ../bin -lgnl_bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o mandatory/$@

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_OBJS) $(BONUS_LIBS) -o bonus/$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
