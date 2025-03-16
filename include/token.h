/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:08:23 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/16 00:36:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <unistd.h>
# include "buffer.h"
# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_NONE = 0,
	TOKEN_LITERAL = 1 << 0,
	TOKEN_INPUT_REDIRECT = 1 << 1,
	TOKEN_HERE_DOC = 1 << 2,
	TOKEN_OUTPUT_REDIRECT = 1 << 3,
	TOKEN_APPEND_REDIRECT = 1 << 4,
	TOKEN_GLOB = 1 << 5,
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
	void 			(*del_func)(void *);
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

t_token_stream	*create_token_stream(void);
void			destroy_token_stream(t_token_stream *stream);
int				realloc_token_stream(t_token_stream *stream, size_t new_cap);
int				append_token_stream(t_token_stream *stream, t_token_type type, char *data);
char			*get_env_name(char *str);
t_token_stream	*tokenizer_arr(char *str, t_msvar *msvar);
void			print_error_unexpected_token(t_token_type t);

typedef struct s_list t_token_node;
typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
}	t_token_list;

t_token_node	*create_token_node(t_token_type type, void *data, void (*del_func)(void *));
t_token_list	*create_token_list(void);
void			destroy_token_list(t_token_list *list);
int				append_token_list(t_token_list *list, t_token_type type, void *data, void (*del_func)(void *));
int				tokenizer_arr_append(t_token_stream *stream, char *str, t_msvar *msvar);
int				read_and_append(t_token_stream *stream, t_msvar *msvar);
int				is_valid(t_token_stream *stream, t_msvar *msvar);
int				is_logical_operator(t_token_type type);

t_token_list	*tokenizer_list(char *str, t_msvar *msvar);
int	is_ceu(t_token_type type);
# ifdef DEBUG

void	print_token(t_token *t);
void	print_token_stream(t_token_stream *ts);
void	print_token_list(t_token_list *list);
t_token_list	*tokenizer_list_expand(char *str, t_msvar *msvar);
# endif	// DEBUG
#endif	// TOKEN_H
