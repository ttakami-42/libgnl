# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttakami <ttakami@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:44:39 by ttakami           #+#    #+#              #
#    Updated: 2022/10/28 22:22:43 by ttakami          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libgnl.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJS	= ${SRCS:.c=.o}
OBJSB	= ${SRCSB:.c=.o}
SRCS	= get_next_line.c get_next_line_utils.c
SRCSB	= get_next_line_bonus.c get_next_line_utils_bonus.c

ifdef WITH_BONUS
ALL_OBJS = $(OBJS) $(OBJSB)
else
ALL_OBJS = $(OBJS)
endif

all:	$(NAME)

$(NAME):	$(ALL_OBJS)
	ar rcs $(NAME) $(ALL_OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(ALL_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus:
	make WITH_BONUS=1

.PHONY: all clean fclean re bonus
