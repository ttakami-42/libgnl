# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttakami <ttakami@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:44:39 by ttakami           #+#    #+#              #
#    Updated: 2023/03/01 19:34:39 by ttakami          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libgnl.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= get_next_line.c get_next_line_utils.c
SRCSB	= get_next_line_bonus.c get_next_line_utils_bonus.c
OBJDIR	= obj
OBJS	= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJSB	= $(addprefix $(OBJDIR)/, $(SRCSB:.c=.o))

ifdef WITH_BONUS
ALL_OBJS = $(OBJSB)
else
ALL_OBJS = $(OBJS)
endif

all:	$(NAME)

$(NAME):	$(ALL_OBJS)
	ar rcs $(NAME) $(ALL_OBJS)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR) ]
	$(CC) -c $(CFLAGS) -o $@ $< $(HEADERPATH)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	make WITH_BONUS=1

.PHONY: all clean fclean re bonus
