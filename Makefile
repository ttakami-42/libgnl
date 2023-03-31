# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttakami <ttakami@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:44:39 by ttakami           #+#    #+#              #
#    Updated: 2023/03/31 12:14:44 by ttakami          ###   ########.fr        #
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

# color codes

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m

# Check if object directory exists, build libft and then the Project

all:	$(NAME)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(OBJDIR)
	@[ -d $(OBJDIR) ]
	@echo "$(YELLOW)      - Compiling :$(RESET)" $<
	$(CC) -c $(CFLAGS) -o $@ $< $(HEADERPATH)

$(NAME):	$(ALL_OBJS)
	@echo "$(YELLOW)\n      - Building $(RESET)$(NAME) $(YELLOW)...\n$(RESET)"
	ar rcs $(NAME) $(ALL_OBJS)
	@echo "$(GREEN)***   Library $(NAME) successfully compiled   ***\n$(RESET)"

clean:
	@echo "$(GREEN)***   Deleting all object from $(NAME)   ...   ***\n$(RESET)"
	@rm -rf $(OBJDIR)
	@echo "done\n"

fclean: clean
	@echo "$(GREEN)***   Deleting executable file from $(NAME)   ...   ***\n$(RESET)"
	@rm -f $(NAME)
	@echo "done\n"

re: fclean all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re bonus
