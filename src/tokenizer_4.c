/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/31 16:23:59 by chakim           ###   ########.fr       */
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

int	tokenizer_arr_append(t_token_stream *stream, char *str, t_msvar *msvar)
{
	t_tokenizer_context	ctx;
	int					status;

	ctx.stream = stream;
	ctx.msvar = msvar;
	ctx.flag_glob = 0;
	ctx.mode = WITHOUT_QUOTE;
	ctx.str_ptr = str;
	ctx.arr = create_gen_arr();
	if (!ctx.arr)
		return (FAILURE);
	clear_buf(msvar->buf);
	if (msvar->command_buf->length > 0)
		append_buf(msvar->command_buf, ' ');
	cat_buf(msvar->command_buf, str);
	run_tokenization_loop(&ctx);
	status = finalize_tokenization(&ctx);
	return (status);
}

int	process_char_single_quote(t_tokenizer_context *ctx)
{
	char	current_char;

	current_char = *ctx->str_ptr;
	if (current_char == '\'')
		ctx->mode = WITHOUT_QUOTE;
	else
	{
		if (append_buf(ctx->msvar->buf, current_char))
			return (FAILURE);
	}
	++ctx->str_ptr;
	return (SUCCESS);
}

int	process_char_double_quote(t_tokenizer_context *ctx)
{
	char	current_char;
	size_t	padding;

	current_char = *ctx->str_ptr;
	if (current_char == '"')
		ctx->mode = WITHOUT_QUOTE;
	else if (current_char == '$')
	{
		padding = expand_dollar_sign_with_quote(ctx->msvar, ctx->str_ptr);
		ctx->str_ptr += padding;
	}
	else
	{
		if (append_buf(ctx->msvar->buf, current_char))
			return (FAILURE);
	}
	++ctx->str_ptr;
	return (SUCCESS);
}

int	run_tokenization_loop(t_tokenizer_context *ctx)
{
	int	status;

	status = SUCCESS;
	while (*ctx->str_ptr)
	{
		if (ctx->mode == WITHOUT_QUOTE)
			status = process_char_without_quote(ctx);
		else if (ctx->mode == SINGLE_QUOTE)
			status = process_char_single_quote(ctx);
		else
			status = process_char_double_quote(ctx);
		if (status == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	finalize_tokenization(t_tokenizer_context *ctx)
{
	int	status;

	status = SUCCESS;
	status = flush_bufs_arr_with_expand_ctx(ctx);
	destroy_gen_arr(ctx->arr, free);
	if (ctx->mode != WITHOUT_QUOTE)
		return (FAILURE);
	return (status);
}
