# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:42:01 by welee             #+#    #+#              #
#    Updated: 2024/06/10 17:23:48 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
BONUS_NAME = libgnl_bonus.a
PUBLIC_DIR = public
SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
BIN_DIR = bin
DOCS_DIR = docs

INCLUDES = -I ${INCLUDES_DIR}
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEFINE = -D BUFFER_SIZE=32
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p
MAKE = make -C

SRCS =	$(SRCS_DIR)/get_next_line.c \
		$(SRCS_DIR)/get_next_line_utils.c
BONUS_SRCS = $(SRCS_DIR)/get_next_line_bonus.c \
			 $(SRCS_DIR)/get_next_line_utils_bonus.c
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

DOXYGEN = doxygen
DOXYGEN_CONFIG = Doxyfile

all: ${NAME}

$(NAME): $(OBJS)
	$(MKDIR) $(BIN_DIR)
	$(LIBC) $(BIN_DIR)/$(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(MKDIR) $(BIN_DIR)
	$(LIBC) $(BIN_DIR)/$(BONUS_NAME) $(BONUS_OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(RM) -r $(DIST_DIR)
	$(MAKE) $(TEST_DIR) clean

fclean: clean
	$(RM) $(BIN_DIR)/$(NAME)

re: fclean all dist

norm:
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCLUDES_DIR)

dist:
	@$(MKDIR) $(DIST_DIR)
	@find $(SRCS_DIR) -type f -exec cp {} $(DIST_DIR) \;
	@find $(INCLUDES_DIR) -type f -exec cp {} $(DIST_DIR) \;
#	@find $(PUBLIC_DIR) -type f -exec cp {} $(DIST_DIR) \;
#	$(MAKE) $(DIST_DIR) all

tests: all
	$(MAKE) $(TEST_DIR) all

tests_bonus: all
	$(MAKE) $(TEST_DIR) bonus

docs:
	${DOXYGEN} ${DOXYGEN_CONFIG}

.PHONY: all clean fclean re norm dist tests docs
