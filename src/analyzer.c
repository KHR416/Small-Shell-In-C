/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:10 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/14 22:56:05 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include <stdlib.h>
#include <libft.h>

t_ast	*create_ast_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast));
	return (node);
}

void	destroy_ast_node(t_ast *node)
{
	// if (!node)
	// 	return ;
	// free(node->left);
	// free(node->right);
	// free(node->data);
	// free(node);
}

int	search_ast(t_ast *root, int order, int (*func)())
{
	// TODO: create post-order DFS
}

int	set_mod(t_quote_mode *mode, char c);

void	set_mode(t_quote_mode *mode, char *str)
{
	*mode = WITHOUT_QUOTE;

}

typedef enum e_token_type
{
	TOKEN_NONE = 0,
	TOKEN_LITERAL = 1 << 0,
	TOKEN_PIPE = 1 << 1,
	TOKEN_INPUT_REDIRECT = 1 << 2,
	TOKEN_HERE_DOC = 1 << 3,
	TOKEN_OUTPUT_REDIRECT = 1 << 4,
	TOKEN_APPEND_REDIRECT = 1 << 5,
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
	size_t	size;
	size_t	cap;
}	t_token_stream;

t_token_stream	*create_token_stream(void)
{
	t_token_stream	*stream;

	stream = malloc(sizeof(t_token_stream));
	if (!stream);
		return (NULL);
	stream->arr = malloc(sizeof(t_token) * 128);
	if (!stream->arr)
	{
		free(stream);
		return (NULL);
	}
	stream->arr[0].type = TOKEN_NONE;
	stream->size = 0;
	stream->cap = 128;
	return (stream);
}

void	destroy_token_stream(t_token_stream *stream)
{
	free(stream->arr);
	free(stream);
}

int	realloc_token_stream(t_token_stream *stream, size_t new_cap)
{
	t_token	*temp;

	temp = ft_realloc(stream->arr, stream->cap, sizeof(t_token) * new_cap);
	if (!temp)
		return (FAILURE);
	stream->arr = temp;
	stream->cap = new_cap;
	return (SUCCESS);
}

int	append_token_stream(t_token_stream *stream, t_token_type type, char *data)
{
	if (stream->size + 1 > stream->cap && realloc_token_stream(stream, stream->cap << 1))
		return (FAILURE);
	stream->arr[stream->size].type = type;
	if (type == TOKEN_LITERAL)
		stream->arr[stream->size].data = data;
	else
		stream->arr[stream->size].data = NULL;
	stream->arr[++stream->size].type = TOKEN_NONE;
	return (SUCCESS);
}

char	*get_path_name(char *str)
{
	char	*name;
	size_t	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		++len;
	name = malloc(len + 1);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, len + 1);
	return (name);
}

size_t	expand_dollar_sign(t_buf *buf, char *str, char **envp)
{
	char	*env_name;
	size_t	padding;

	++str;
	if (*str == '?')
	{
		cat_buf(buf, "EXIT_STATUS");
		padding = 1;
	}
	else if (ft_isalpha(*str) || *str == '_')
	{
		env_name = get_path_name(str);
		cat_buf(buf, ms_getenv(env_name, envp));
		padding = ft_strlen(env_name);
		free(env_name);
	}
	else
	{
		append_buf(buf, '$');
		padding = 0;
	}
	return (padding);
}

t_token	*tokenizer(char *str, char **envp)
{
	t_token_stream	*stream = create_token_stream();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();

	while (*str)
	{
		if (mode == WITHOUT_QUOTE)
		{
			if (*str == '\'')
				mode = SINGLE_QUOTE;
			else if (*str == '"')
				mode = DOUBLE_QUOTE;
			else if (*str == '$')
				str += expand_dollar_sign(buf, str, envp);
			else if (*str == ' ')
			{
				append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
				buf = create_buf();
			}
			else if (*str == '<')
			{
				if (buf->length)
				{
					append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
					buf = create_buf();
				}
				if (*(str + 1) == '<')
				{
					append_token_stream(stream, TOKEN_HERE_DOC, NULL);
					++str;
				}
				else
					append_token_stream(stream, TOKEN_INPUT_REDIRECT, NULL);
			}
			else if (*str == '>')
			{
				if (buf->length)
				{
					append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
					buf = create_buf();
				}
				if (*(str + 1) == '>')
				{
					append_token_stream(stream, TOKEN_APPEND_REDIRECT, NULL);
					++str;
				}
				else
					append_token_stream(stream, TOKEN_OUTPUT_REDIRECT, NULL);
			}
			else if (*str == '|')
			{
				if (buf->length)
				{
					append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
					buf = create_buf();
				}
				append_token_stream(stream, TOKEN_PIPE, NULL);
			}
			else
				append_buf(buf, *str);
			++str;
		}
		else if (mode == SINGLE_QUOTE)
		{
			if (*str == '\'')
				mode = WITHOUT_QUOTE;
			else
				append_buf(buf, *str);
			++str;
		}
		else
		{
			if (*str == '"')
				mode = WITHOUT_QUOTE;
			else if (*str == '$')
				str += expand_dollar_sign(buf, str, envp);
			else
				append_buf(buf, *str);
			++str;
		}
	}
	if (buf->length)
	{
		append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
		buf = NULL;
	}
	destroy_buf(buf);
	t_token 	*arr = stream->arr;
	free(stream);
	return (arr);
}

t_ast	*analyzer(t_token *token_arr)
{
	// TODO: create ast
	// lexicon priority: '\', "'> '&&, ||' > '|' > '>, >>, <, <<'
	// syntax priority: suffix > prefix
	t_ast			*root;

	root = create_ast_node();
	if (!root)
		return (NULL);
	interpret_quote(token_arr);
	interpret_pipe(root, token_arr);
	interpret_redir_out(root, token_arr);
	interpret_redir_in(root, token_arr);
	interpret_cmd(root, token_arr);
	return (root);
}
