/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/06 21:00:41 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <unistd.h>
# include "buffer.h"

typedef enum e_token_type
{
	TOKEN_NONE = 0,
	TOKEN_LITERAL = 1 << 0,
	TOKEN_INPUT_REDIRECT = 1 << 1,
	TOKEN_HERE_DOC = 1 << 2,
	TOKEN_OUTPUT_REDIRECT = 1 << 3,
	TOKEN_APPEND_REDIRECT = 1 << 4,
	TOKEN_PIPE = 1 << 5,
	// TOKEN_AND_OPERATOR = 1 << 6,
	// TOKEN_OR_OPERATOR = 1 << 7,
	// TOKEN_PARENTHESIS_OPEN = 1 << 8,
	// TOKEN_PARENTHESIS_CLOSE = 1 << 9,
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
}	t_token_stream;

typedef enum e_quote_mode
{
	WITHOUT_QUOTE = 0,
	SINGLE_QUOTE = (1 << 0),
	DOUBLE_QUOTE = (1 << 1),
}	t_quote_mode;

int	set_mod(t_quote_mode *mode, char c);
t_token_stream	*create_token_stream(void);
void	destroy_token_stream(t_token_stream *stream);
int	realloc_token_stream(t_token_stream *stream, size_t new_cap);
int	append_token_stream(t_token_stream *stream, t_token_type type, char *data);
char	*get_path_name(char *str);
size_t	expand_dollar_sign(t_buf *buf, char *str, char **envp);
t_token_stream	*tokenizer(char *str, char **envp);
void	print_token(t_token *t);
void	print_token_stream(t_token_stream *ts);
void	print_error_unexpected_token(t_token_type t);
#endif
