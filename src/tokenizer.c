/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/12 21:31:29 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

int	set_mod(t_quote_mode *mode, char c)
{
	if (c == '\'')
	{
		if (*mode == DOUBLE_QUOTE)
			return (FAILURE);
		else if (*mode == SINGLE_QUOTE)
			*mode = WITHOUT_QUOTE;
		else if (*mode == WITHOUT_QUOTE)
			*mode = SINGLE_QUOTE;
		return (SUCCESS);
	}
	else if (c == '\"')
	{
		if (*mode == SINGLE_QUOTE)
			return (FAILURE);
		else if (*mode == DOUBLE_QUOTE)
			*mode = WITHOUT_QUOTE;
		else if (*mode == WITHOUT_QUOTE)
			*mode = DOUBLE_QUOTE;
		return (SUCCESS);
	}
	return (FAILURE);
}

#define TOKEN_STREAM_INITIAL_CAP	4

t_token_stream	*create_token_stream(void)
{
	t_token_stream	*stream;

	stream = malloc(sizeof(t_token_stream));
	if (!stream)
		return (NULL);
	stream->arr = malloc(sizeof(t_token) * TOKEN_STREAM_INITIAL_CAP);
	if (!stream->arr)
	{
		free(stream);
		return (NULL);
	}
	stream->arr[0].type = TOKEN_NONE;
	stream->len = 0;
	stream->cap = TOKEN_STREAM_INITIAL_CAP;
	return (stream);
}

void	destroy_token_stream(t_token_stream *stream)
{
	size_t	i;

	i = 0;
	while (stream->arr[i].type != TOKEN_NONE)
		free(stream->arr[i++].data);
	free(stream->arr);
	free(stream);
}

int	realloc_token_stream(t_token_stream *stream, size_t new_cap)
{
	t_token	*temp;

	temp = ft_realloc(stream->arr, sizeof(t_token) * stream->cap, sizeof(t_token) * new_cap);
	if (!temp)
		return (FAILURE);
	stream->arr = temp;
	stream->cap = new_cap;
	return (SUCCESS);
}

int	append_token_stream(t_token_stream *stream, t_token_type type, char *data)
{
	if (stream->cap < stream->len + 2 && realloc_token_stream(stream, stream->cap << 1))
		return (FAILURE);
	stream->arr[stream->len].type = type;
	if (type == TOKEN_LITERAL)
		stream->arr[stream->len].data = data;
	else
		stream->arr[stream->len].data = NULL;
	stream->arr[++stream->len].type = TOKEN_NONE;
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

size_t	expand_dollar_sign(t_buf *buf, char *str, t_msvar *msvar)
{
	char	*env_name;
	size_t	padding;

	++str;
	if (*str == '?')
	{
		if (msvar->wstatus >= 100)
			append_buf(buf, msvar->wstatus / 100 + '0');
		if (msvar->wstatus >= 10)
			append_buf(buf, msvar->wstatus / 10 % 10 + '0');
		append_buf(buf, msvar->wstatus % 10 + '0');
		padding = 1;
	}
	else if (ft_isalpha(*str) || *str == '_')
	{
		env_name = get_path_name(str);
		cat_buf(buf, ms_getenv(env_name, msvar->envp));
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

t_token_stream	*tokenizer(char *str, t_msvar *msvar)
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
				str += expand_dollar_sign(buf, str, msvar);
			else if (*str == ' ')
			{
				if (buf->length)
				{
					append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
					buf = create_buf();
				}
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
				str += expand_dollar_sign(buf, str, msvar);
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
	return (stream);
}

void	print_token(t_token *t)
{
	#ifdef DEBUG
	if (t->type == TOKEN_LITERAL)
		fprintf(stderr, "LITERAL: %s\n", t->data);
	else if (t->type == TOKEN_PIPE)
		fprintf(stderr, "|\n");
	else if (t->type == TOKEN_INPUT_REDIRECT)
		fprintf(stderr, "<\n");
	else if (t->type == TOKEN_HERE_DOC)
		fprintf(stderr, "<<\n");
	else if (t->type == TOKEN_OUTPUT_REDIRECT)
		fprintf(stderr, ">\n");
	else if (t->type == TOKEN_APPEND_REDIRECT)
		fprintf(stderr, ">>\n");
	else
		fprintf(stderr, "unknown token\n");
	#endif
}

void	print_token_stream(t_token_stream *ts)
{
	#ifdef DEBUG
	for (size_t i = 0; ts->arr[i].type != TOKEN_NONE; ++i)
		print_token(ts->arr + i);
	#endif
}
