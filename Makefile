# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 14:24:10 by ccariou           #+#    #+#              #
#    Updated: 2023/02/06 22:41:09 by teppo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in 
HEAD 	= lemin.h
# compile specs
FLAGS 	= -Werror -Wextra -Wall -g
CC 		= gcc
LFT 	= -L ./libft/ -lft

# SOURCES FILES 
SRC_DIR = ./srcs/
SRCS 	= main.c ants.c map.c rooms.c helpers.c init.c links.c solve.c queue.c path.c \
		  move_ants.c grouping.c bittricks.c storage.c

INC 	= -I./include
INC_LFT = -I./libft/includes 
LIB		=	./libft/libft.a

#OBJECTS
OBJ_DIR = ./object/
OBJ 	= $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))

debug: LDFLAGS += -fsanitize=address -fsanitize=undefined \
	-fno-sanitize-recover=all -fno-sanitize=null -fno-sanitize=alignment 
debug: all

all: $(NAME) 

$(NAME): $(LIB) $(OBJ)
	-@$(CC) $(FLAGS) $(INC_LFT) $(INC) -o $(NAME) $(OBJ) $(LFT)
	-@echo "Program compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	-@mkdir -p $(OBJ_DIR)
	-@$(CC) $(FLAGS) $(INC_LFT) $(INC) -o $@ -c $<

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
