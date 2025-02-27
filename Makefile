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
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS := -L$(LIB_DIR) -lft -lreadline

ifdef DEBUG
CFLAGS += -g -D DEBUG
SRC_DEBUG := \
	tokenizer_debug.c\
	ceu_debug.c\
	pipe_seg_debug.c
endif

ifdef MEMCHECK
CFLAGS  += -D MEMCHECK
endif

SRC := \
	analyzer.c \
	buffer_0.c \
	buffer_1.c \
	builtin_utils.c \
	ceu.c \
	ceu_exec.c \
	envp_0.c \
	envp_1.c \
	main.c \
	ms_cd.c \
	ms_echo.c \
	ms_echo_n_option.c \
	ms_env.c \
	ms_exit.c \
	ms_export.c \
	ms_getcwd.c \
	ms_pwd.c \
	ms_signal.c \
	ms_unset.c \
	ms_var_init.c \
	pipe_seg.c \
	pipe_seg_exec.c \
	readline.c \
	tokenizer_0.c \
	tokenizer_1.c \
	$(SRC_DEBUG)

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

vpath %.c $(SRC_DIR) $(TEST_SRC_DIR)

.PHONY: all clean fclean re bonus

all: $(MINISHELL)

$(MINISHELL): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o:	%.c | $(LIBFT_HDR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(LIB_DIR):
	mkdir -p $@

$(LIBFT): | $(LIBFT_DIR) $(LIB_DIR)
	$(MAKE) -C $(LIBFT_DIR) all
	cp $(LIBFT_DIR)/libft.a $(LIBFT)

$(LIBFT_HDR): $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.h $(LIBFT_HDR)

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

OBJ_WO_MAIN := $(filter-out $(OBJ_DIR)/main.o, $(OBJ))

test_%: $(OBJ_WO_MAIN) $(LIBFT) $(OBJ_DIR)/test_%_main.o | $(OBJ_DIR)
	$(CC) $(OBJ_WO_MAIN) $(OBJ_DIR)/$@_main.o $(LDFLAGS) -o $@

clean_test: clean
	rm -f test_*
