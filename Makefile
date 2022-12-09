# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/09 08:30:23 by kaheinz           #+#    #+#              #
#    Updated: 2022/12/08 15:17:10 by ksura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = gcc
CFLAGS := -Wall -Werror -Wextra -g
HEADER = ./header
SRCDIR = ./srcs/
OBJDIR := ./build/
LIBS = -lm
LIBFT_DIRECTORY = ./libft
LIBFT = $(LIBFT_DIRECTORY)/libft.a
MINILIB_DIR = ./mlx
FT_INC	= -I ./libft/ -I ./mlx/

GREEN = \033[0;32m
RED = \033[0;31m

SRCS = main.c

OS = $(shell uname)
# ifeq ($(OS), Linux)
# FLAGS_OS = -lreadline
# endif
# ifeq ($(OS), Darwin)
# FLAGS_OS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
# endif
ifeq ($(OS), Linux)
	LIBS += -Lmlx -lmlx -L/usr/lib -lX11 -lXext -lz 
#	-Imlx 
	OBLI += -I/usr/inlcude -Imlx
	SRCS += destroy_linux.c
endif
ifeq ($(OS), Darwin)
	LIBS += -Lmlx -lmlx -framework OpenGL -framework AppKit
	SRCs += destroy_mac.c
endif

OBJS = $(SRCS:.c=.o)
OBJECTS_PREF := $(addprefix $(OBJDIR), $(OBJS))

all: $(NAME)

# $(NAME): $(OBJECTS_PREF) $(OBJDIR)
# 	make -C $(LIBFT_DIRECTORY)
# 	$(CC) $(CFLAGS) $(OBJECTS_PREF) $(LIBFT) -I$(HEADER) -o $@ $(OBJS) $(LIBFT) $(FLAGS_OS)

$(NAME):$(OBJECTS_PREF) $(OBJDIR)
	@make -C $(LIBFT_DIRECTORY)
	@$(CC) $(CFLAGS) $(OBJECTS_PREF) $(LIBFT) -I$(HEADER) $(FLAGS) $(LIBS) -o $@
	@echo "$(GREEN)$(NAME) was created"

# $(NAME):$(OBJECTS_PREF) $(OBJDIR)
# 	@make -C $(LIBFT_DIRECTORY)
# 	@$(CC) $(CFLAGS) $(OBJECTS_PREF) $(LIBFT) -I$(HEADER) $(FLAGS) -o $@ $(FLAGS_OS)
# 	@echo "$(GREEN)$(NAME) was created"

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(OBJECTS_PREF): build/%.o : srcs/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(OBLI) -c $< -o $@ -I$(HEADER) $(FT_INC)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "$(RED)$(NAME) was deleted"

re: fclean all 

.PHONY: all clean fclean re

