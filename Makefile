HEADER_DIR		:= ./include/
LIBHEADER_DIR	:= ./libft/includes/
LIB_DIR			:= ./libft/
SRC_DIR			:= ./srcs/
OBJ_DIR			:= ./obj/

#TODO: replace with actual file list
SRC 	:= $(wildcard $(SRC_DIR)*.c)

DEP 	:= $(HEADER_DIR)lemin.h

OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			:= gcc
CFLAGS		:= -g -c -Wall -Wextra -Werror
CPPFLAGS 	:= -I$(LIBHEADER_DIR) -I$(HEADER_DIR)
LDFLAGS 	:= -L$(LIB_DIR)
LDLIBS 		:= -lft

BIN := lem-in

.PHONY: all clean fclean re

all: lib $(BIN)
	echo $(_SRC)

lib:
	make -C $(LIB_DIR)
	echo "Compiled library"

$(BIN): $(OBJ_DIR) $(OBJ)
	echo "Compiled objs"
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)
	echo "Compiled $(BIN)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR):
	/bin/mkdir -p $@
	echo "Made obj dir"

clean:
	if [ -d "$(OBJ_DIR)" ]; \
		then /bin/rm -rf $(OBJ_DIR); echo "Removed objs"; fi
	make -C $(LIB_DIR) clean

fclean: clean
	make -C $(LIB_DIR) fclean
	/bin/rm -f $(BIN)
	echo "Removed $(BIN)"

re: fclean all
