LIB_DIR := lib
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft

LIBFT := $(LIB_DIR)/libft.a
LIBFT_HDR := $(INC_DIR)/libft.h

MINISHELL := minishell

CC := cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
ifdef DEBUG
	CFLAGS += -g
endif
LDFLAGS := -Llib -lft -lreadline

# TODO: Write all source files
SRC :=
OBJ := $(SRC:.c=.o)

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)

.PHONY: all clean fclean re bonus

all: $(MINISHELL)

$(MINISHELL): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ): %.o: %.c $(LIBFT_HDR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

clean:
	rm -rf $(OBJ_DIR)
# TODO: Remove object files of libft

fclean: clean
	rm -f $(MINISHELL)
# TODO: Remove libft

re:
	$(MAKE) fclean
	$(MAKE) all

# bonus:
# TODO: Complete dependencies and recipes