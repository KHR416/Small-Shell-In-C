LIB_DIR := lib
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
LIBFT_DIR := libft
BONUS_SRC_DIR := bonus_src

LIBFT := $(LIB_DIR)/libft.a
LIBFT_HDR := $(INC_DIR)/libft.h
MINISHELL := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS := -L$(LIB_DIR) -lft -lreadline

ifdef DEBUG
CFLAGS += -g -D DEBUG
endif

SRC := \
	ast_0.c \
	ast_1.c \
	ast_analyzer_0.c \
	ast_analyzer_1.c \
	ast_analyzer_2.c \
	ast_traversal_0.c \
	buffer_0.c \
	buffer_1.c \
	builtin_utils.c \
	ceu_0.c \
	ceu_1.c \
	ceu_2.c \
	ceu_exec_0.c \
	ceu_exec_1.c \
	ceu_exec_2.c \
	ceu_parser.c \
	envp_0.c \
	envp_1.c \
	generic_array_0.c \
	generic_array_1.c \
	generic_array_2.c \
	is_valid_0.c \
	is_valid_1.c \
	is_valid_token.c \
	main.c \
	ms_cd.c \
	ms_cd_utils.c \
	ms_echo.c \
	ms_echo_n_option.c \
	ms_env.c \
	ms_exit.c \
	ms_export.c \
	ms_export_utils.c \
	ms_getcwd.c \
	ms_glob.c \
	ms_pwd.c \
	ms_signal.c \
	ms_unset.c \
	ms_var_init.c \
	stack.c \
	stack_create.c \
	token_0.c \
	tokenizer_0.c \
	tokenizer_1.c \
	tokenizer_2.c \
	tokenizer_3.c \
	tokenizer_4.c \
	tokenizer_5.c \
	token_stream_0.c \
	token_stream_1.c \
	wrapper_0.c \
	main_helper.c \
	ms_signal_helper.c

BONUS_SRC = \
	ast_0_bonus.c \
	ast_1_bonus.c \
	ast_analyzer_0_bonus.c \
	ast_analyzer_1_bonus.c \
	ast_analyzer_2_bonus.c \
	ast_traversal_0_bonus.c \
	buffer_0_bonus.c \
	buffer_1_bonus.c \
	builtin_utils_bonus.c \
	ceu_0_bonus.c \
	ceu_1_bonus.c \
	ceu_2_bonus.c \
	ceu_exec_0_bonus.c \
	ceu_exec_1_bonus.c \
	ceu_exec_2_bonus.c \
	ceu_parser_bonus.c \
	envp_0_bonus.c \
	envp_1_bonus.c \
	generic_array_0_bonus.c \
	generic_array_1_bonus.c \
	generic_array_2_bonus.c \
	is_valid_0_bonus.c \
	is_valid_1_bonus.c \
	is_valid_token_bonus.c \
	main_bonus.c \
	main_helper_bonus.c \
	ms_cd_bonus.c \
	ms_cd_utils_bonus.c \
	ms_echo_bonus.c \
	ms_echo_n_option_bonus.c \
	ms_env_bonus.c \
	ms_exit_bonus.c \
	ms_export_bonus.c \
	ms_export_utils_bonus.c \
	ms_getcwd_bonus.c \
	ms_glob_bonus.c \
	ms_pwd_bonus.c \
	ms_signal_bonus.c \
	ms_signal_helper_bonus.c \
	ms_unset_bonus.c \
	ms_var_init_bonus.c \
	stack_bonus.c \
	stack_create_bonus.c \
	token_0_bonus.c \
	tokenizer_0_bonus.c \
	tokenizer_1_bonus.c \
	tokenizer_2_bonus.c \
	tokenizer_3_bonus.c \
	tokenizer_4_bonus.c \
	tokenizer_5_bonus.c \
	token_stream_0_bonus.c \
	token_stream_1_bonus.c \
	wrapper_0_bonus.c

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

BONUS_OBJ := $(addprefix $(OBJ_DIR)/,$(BONUS_SRC:.c=.o))

vpath %.c $(SRC_DIR) $(BONUS_SRC_DIR)

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

$(LIBFT_HDR): | $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.h $(LIBFT_HDR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(MINISHELL)
	rm -f $(LIBFT_HDR)
	rm -rf $(LIB_DIR)
	rm -f .bonus
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.bonus: $(BONUS_OBJ) $(LIBFT)
	$(CC) $(BONUS_OBJ) $(LDFLAGS) -o $(MINISHELL)
	touch .bonus

bonus: .bonus
