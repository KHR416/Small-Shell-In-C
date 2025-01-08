CC := cc
CFLAGS = -Wall -Wextra -Werror -I.
ifdef DEBUG
	CFLAGS += -g
endif

SRC_DIR := src
PRINTF_SRC_DIR := $(SRC_DIR)/ft_printf
GNL_SRC_DIR := $(SRC_DIR)/get_next_line
OBJ_DIR := obj

LIBFT := libft.a

SRC := \
	ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_itoa.c\
	ft_lstadd_back.c\
	ft_lstadd_front.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstlast.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_lstsize.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_realloc.c\
	ft_split.c\
	ft_strchr.c\
	ft_strcmp.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	flag_predicate.c\
	ft_printf.c\
	parse_conversion.c\
	print_conversion_c.c\
	print_conversion_d.c\
	print_conversion_p.c\
	print_conversion_s.c\
	print_conversion_u.c\
	print_conversion_x.c\
	put1.c\
	put2.c\
	struct_utils.c\
	utils.c\
	get_next_line.c\
	get_next_line_utils.c
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

vpath %.c $(SRC_DIR) $(PRINTF_SRC_DIR) $(GNL_SRC_DIR)

.PHONY: all clean fclean re

all: $(LIBFT)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT)

re:
	$(MAKE) fclean
	$(MAKE) all

$(LIBFT): $(OBJ)
	ar -rcs $@ $^

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)