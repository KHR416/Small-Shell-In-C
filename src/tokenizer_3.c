/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/03 21:19:44 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "generic_array.h"
#include "wrapper.h"

int	handle_logical_pipe_operator(t_tokenizer_context *ctx, \
	char c1, char c2)
{
	if (c1 == '|' && c2 == '|')
	{
		if (append_token_stream(ctx->stream, TOKEN_OR_OPERATOR, NULL))
			return (FAILURE);
		++ctx->str_ptr;
	}
	else if (c1 == '|')
	{
		if (append_token_stream(ctx->stream, TOKEN_PIPE, NULL))
			return (FAILURE);
	}
	else
	{
		if (append_token_stream(ctx->stream, TOKEN_AND_OPERATOR, NULL))
			return (FAILURE);
		++ctx->str_ptr;
	}
	return (SUCCESS);
}

int	handle_parenthesis_operator(t_tokenizer_context *ctx, char c1)
{
	if (c1 == '(')
	{
		if (append_token_stream(ctx->stream, TOKEN_PARENTHESIS_OPEN, NULL))
			return (FAILURE);
	}
	else
	{
		if (append_token_stream(ctx->stream, TOKEN_PARENTHESIS_CLOSE, NULL))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_char_operator(t_tokenizer_context *ctx)
{
	char	c1;
	char	c2;
	int		status;

	if (flush_bufs_arr_with_expand_ctx(ctx))
		return (FAILURE);
	c1 = *(ctx->str_ptr);
	c2 = *(ctx->str_ptr + 1);
	if (c1 == '<' || c1 == '>')
		status = handle_redirect_operator(ctx, c1, c2);
	else if (c1 == '|' || (c1 == '&' && c2 == '&'))
		status = handle_logical_pipe_operator(ctx, c1, c2);
	else if (c1 == '(' || c1 == ')')
		status = handle_parenthesis_operator(ctx, c1);
	else
		status = SUCCESS;
	if (status == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	handle_char_dollar(t_tokenizer_context *ctx)
{
	size_t	padding;

	padding = expand_dollar_sign(ctx);
	ctx->str_ptr += padding;
	return (SUCCESS);
}

int	handle_char_asterisk(t_tokenizer_context *ctx)
{
	if (ctx->msvar->buf->length)
	{
		if (append_gen_arr(ctx->arr, ctx->msvar->buf->buffer, ft_strdup_wrap))
			return (FAILURE);
		clear_buf(ctx->msvar->buf);
	}
	if (append_gen_arr(ctx->arr, "", ft_strdup_wrap))
		return (FAILURE);
	ctx->flag_glob = 1;
	return (SUCCESS);
}
