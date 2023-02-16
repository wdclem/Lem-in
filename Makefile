# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 14:24:10 by ccariou           #+#    #+#              #
#    Updated: 2023/02/16 11:03:24 by tpolonen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in 
HEAD 	= lemin.h
# compile specs
FLAGS 	= -Werror -Wextra -Wall -g
DFLAGS  = -fsanitize=address -fsanitize=undefined \
	-fno-sanitize-recover=all -fno-sanitize=null -fno-sanitize=alignment 
CC 		= gcc
LFT 	= -L ./libft/ -lft

# SOURCES FILES 
SRC_DIR = ./srcs/
SRCS 	= main.c ants.c map.c rooms.c helpers.c init.c links.c link_helpers.c \
		  solve.c queue.c path.c move_ants.c grouping.c bitmask_single.c \
		  bitmask_group.c storage.c error_management.c flowmap.c

INC 	= -I./include
INC_LFT = -I./libft/includes 
LIB		=	./libft/libft.a

#OBJECTS
OBJ_DIR = ./object/
OBJ 	= $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))

all: $(NAME) 

debug: FLAGS += $(DFLAGS)
debug: all

$(NAME): $(LIB) $(OBJ)
	$(CC) $(FLAGS) $(INC_LFT) $(INC) -o $(NAME) $(OBJ) $(LFT)
	-@echo "Program compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	-@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INC_LFT) $(INC) -o $@ -c $<

$(LIB):
	-@make -C ./libft/ 

clean:
	-@rm -rf $(OBJ_DIR)
	-@make -C ./libft clean

fclean: clean
	-@rm -f $(NAME)
	-@make  -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
