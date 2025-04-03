/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/31 15:45:55 by chakim           ###   ########.fr       */
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

int	add_buffer_to_glob_array(t_tokenizer_context *ctx)
{
	if (ctx->msvar->buf->length > 0)
	{
		if (append_gen_arr(ctx->arr, ctx->msvar->buf->buffer, ft_strdup_wrap))
			return (FAILURE);
		clear_buf(ctx->msvar->buf);
	}
	return (SUCCESS);
}

char	**prepare_glob_data(t_tokenizer_context *ctx)
{
	char	**data;

	data = malloc((ctx->arr->length + 1) * sizeof(void *));
	if (!data)
		return (NULL);
	ft_memcpy(data, ctx->arr->data, ctx->arr->length * sizeof(void *));
	data[ctx->arr->length] = NULL;
	clear_gen_arr(ctx->arr);
	return (data);
}

int	execute_glob_and_handle_result(t_tokenizer_context *ctx, char **data)
{
	char	**glob_results;
	int		status;

	glob_results = ms_glob(data);
	if (!glob_results)
		return (FAILURE);
	if (!(*glob_results))
		status = handle_glob_no_match(ctx->stream, data);
	else
		status = handle_glob_match(ctx->stream, glob_results);
	destroy_split(glob_results);
	return (status);
}

int	expand_glob_with_arr(t_tokenizer_context *ctx)
{
	char	**data;
	int		status;

	status = add_buffer_to_glob_array(ctx);
	if (status == FAILURE)
		return (FAILURE);
	data = prepare_glob_data(ctx);
	if (!data)
		return (FAILURE);
	status = execute_glob_and_handle_result(ctx, data);
	destroy_void_arr((void **)data, free);
	return (status);
}

int	handle_redirect_operator(t_tokenizer_context *ctx, char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
	{
		if (append_token_stream(ctx->stream, TOKEN_HERE_DOC, NULL))
			return (FAILURE);
		++ctx->str_ptr;
	}
	else if (c1 == '<')
	{
		if (append_token_stream(ctx->stream, TOKEN_INPUT_REDIRECT, NULL))
			return (FAILURE);
	}
	else if (c1 == '>' && c2 == '>')
	{
		if (append_token_stream(ctx->stream, TOKEN_APPEND_REDIRECT, NULL))
			return (FAILURE);
		++ctx->str_ptr;
	}
	else
	{
		if (append_token_stream(ctx->stream, TOKEN_OUTPUT_REDIRECT, NULL))
			return (FAILURE);
	}
	return (SUCCESS);
}
