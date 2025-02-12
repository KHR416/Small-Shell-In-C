LIB_DIR := lib
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft
TEST_SRC_DIR := test

LIBFT := $(LIB_DIR)/libft.a
LIBFT_HDR := $(INC_DIR)/libft.h

MINISHELL := minishell

CC := cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
ifdef DEBUG
	CFLAGS += -g -D DEBUG
endif
LDFLAGS := -Llib -lft -lreadline

# TODO: Write all source files

SRC := \
	analyzer.c\
	buffer_0.c\
	buffer_1.c\
	envp_0.c\
	envp_1.c\
	readline.c\
	tokenizer.c\
	ceu.c\
	pipe_seg.c\
	ceu_exec.c\
	ms_var_init.c\
	pipe_seg_exec.c
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re bonus

all: $(MINISHELL)

$(MINISHELL): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(LIBFT_HDR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(LIBFT_HDR)
	rm -rf $(LIB_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

$(LIB_DIR):
	mkdir -p $@

 $(OBJ_DIR):
	mkdir -p $@

$(LIBFT): | $(LIBFT_DIR) $(LIB_DIR)
	$(MAKE) -C $(LIBFT_DIR) all
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_HDR) : $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.h $(LIBFT_HDR)

test_token:	$(OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC_DIR)/$@_main.c -o $(OBJ_DIR)/$@_main.o
	$(CC) $(OBJ) $(OBJ_DIR)/$@_main.o $(LDFLAGS)

test_ceu:	$(OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC_DIR)/$@_main.c -o $(OBJ_DIR)/$@_main.o
	$(CC) $(OBJ) $(OBJ_DIR)/$@_main.o $(LDFLAGS)

test_pipe_seg:	$(OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC_DIR)/$@_main.c -o $(OBJ_DIR)/$@_main.o
	$(CC) $(OBJ) $(OBJ_DIR)/$@_main.o $(LDFLAGS)

test_ceu_exec:	$(OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC_DIR)/$@_main.c -o $(OBJ_DIR)/$@_main.o
	$(CC) $(OBJ) $(OBJ_DIR)/$@_main.o $(LDFLAGS)

test_pipe_seg_exec:	$(OBJ) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TEST_SRC_DIR)/$@_main.c -o $(OBJ_DIR)/$@_main.o
	$(CC) $(OBJ) $(OBJ_DIR)/$@_main.o $(LDFLAGS)

# bonus:
# TODO: Complete dependencies and recipes
