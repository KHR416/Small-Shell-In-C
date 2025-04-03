/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/31 15:02:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <unistd.h>
# include "buffer.h"
# include "minishell.h"
# include "generic_array.h"

typedef enum e_token_type
{
	TOKEN_NONE = 0,
	TOKEN_LITERAL = 1 << 0,
	TOKEN_INPUT_REDIRECT = 1 << 1,
	TOKEN_HERE_DOC = 1 << 2,
	TOKEN_OUTPUT_REDIRECT = 1 << 3,
	TOKEN_APPEND_REDIRECT = 1 << 4,
	TOKEN_PIPE = 1 << 6,
	TOKEN_AND_OPERATOR = 1 << 7,
	TOKEN_OR_OPERATOR = 1 << 8,
	TOKEN_PARENTHESIS_OPEN = 1 << 9,
	TOKEN_PARENTHESIS_CLOSE = 1 << 10,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*data;
}	t_token;

typedef struct s_token_stream
{
	t_token	*arr;
	size_t	len;
	size_t	cap;
	size_t	offset;
}	t_token_stream;

typedef enum e_quote_mode
{
	WITHOUT_QUOTE = 0,
	SINGLE_QUOTE = (1 << 0),
	DOUBLE_QUOTE = (1 << 1),
}	t_quote_mode;

typedef struct s_tokenizer_context
{
	t_token_stream	*stream;
	t_msvar			*msvar;
	t_gen_arr		*arr;
	int				flag_glob;
	t_quote_mode	mode;
	char			*str_ptr;
}	t_tokenizer_context;

t_token_stream	*create_token_stream(void);
void			destroy_token_stream(t_token_stream *stream);
int				realloc_token_stream(t_token_stream *stream, size_t new_cap);
int				append_token_stream(
					t_token_stream *stream,
					t_token_type type,
					char *data);
char			*get_env_name(char *str);
void			print_error_unexpected_token(t_token_type t);
int				read_line_and_extend_stream(
					t_token_stream *stream,
					t_msvar *msvar);
int				validate_and_extend_stream(
					t_token_stream *stream,
					t_msvar *msvar);
int				is_operator_token(t_token_type type);
int				is_ceu_token(t_token_type type);
int				is_redirect_token(t_token_type type);
int				is_input_redirect_token(t_token_type type);
int				is_output_redirect_token(t_token_type type);
int				is_ceu_token(t_token_type type);
void			print_token_type(t_token_type type, int fd);
t_token			*read_token_stream(t_token_stream *stream);
t_token			*peek_token_stream(t_token_stream *stream, ssize_t offset);
void			process_exit_status(t_msvar *msvar);
int				read_line_and_extend_stream(t_token_stream \
	*stream, t_msvar *msvar);
int				flush_bufs_arr_with_expand_ctx(t_tokenizer_context *ctx);
size_t			handle_dollar_qmark(t_msvar *msvar);
size_t			handle_dollar_var(t_tokenizer_context *ctx, \
	const char *env_val);
size_t			handle_dollar_variable_expansion(t_tokenizer_context *ctx);
size_t			expand_dollar_sign(t_tokenizer_context *ctx);
size_t			handle_dollar_variable_expansion_quoted(t_msvar *msvar, \
	char *current_str_pos);
size_t			expand_dollar_sign_with_quote(t_msvar *msvar, char *str_ptr);
int				handle_glob_no_match(t_token_stream *stream, char **data);
int				handle_glob_match(t_token_stream *stream, char \
	**glob_results);
int				add_buffer_to_glob_array(t_tokenizer_context *ctx);
char			**prepare_glob_data(t_tokenizer_context *ctx);
int				execute_glob_and_handle_result(t_tokenizer_context \
	*ctx, char **data);
int				expand_glob_with_arr(t_tokenizer_context *ctx);
int				handle_redirect_operator(t_tokenizer_context \
	*ctx, char c1, char c2);
int				handle_logical_pipe_operator(t_tokenizer_context *ctx, \
	char c1, char c2);
int				handle_parenthesis_operator(t_tokenizer_context *ctx, char c1);
int				handle_char_operator(t_tokenizer_context *ctx);
int				handle_char_dollar(t_tokenizer_context *ctx);
int				handle_char_asterisk(t_tokenizer_context *ctx);
int				process_char_without_quote(t_tokenizer_context *ctx);
int				process_char_single_quote(t_tokenizer_context *ctx);
int				process_char_double_quote(t_tokenizer_context *ctx);
int				run_tokenization_loop(t_tokenizer_context *ctx);
int				finalize_tokenization(t_tokenizer_context *ctx);
int				tokenizer_arr_append(t_token_stream *stream, \
	char *str, t_msvar *msvar);

# ifdef DEBUG

void			print_token(t_token *t);
void			print_token_stream(t_token_stream *ts);
# endif	// DEBUG
#endif	// TOKEN_H
