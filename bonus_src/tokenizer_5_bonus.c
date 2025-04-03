/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/03 21:20:05 by wchoe            ###   ########.fr       */
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
#include <readline/readline.h>

static int	handle_special_or_operator(t_tokenizer_context *ctx, char c)
{
	if (c == '$')
		return (handle_char_dollar(ctx));
	else if (c == '*')
		return (handle_char_asterisk(ctx));
	else if (c == ' ')
		return (flush_bufs_arr_with_expand_ctx(ctx));
	else
		return (handle_char_operator(ctx));
}

static int	handle_default_char_append(t_tokenizer_context *ctx, char c)
{
	if (append_buf(ctx->msvar->buf, c))
		return (FAILURE);
	return (SUCCESS);
}

int	process_char_without_quote(t_tokenizer_context *ctx)
{
	char	current_char;
	int		status;

	status = SUCCESS;
	current_char = *ctx->str_ptr;
	if (current_char == '\'')
		ctx->mode = SINGLE_QUOTE;
	else if (current_char == '"')
		ctx->mode = DOUBLE_QUOTE;
	else if (ft_strchr("$* <>|&()", current_char))
		status = handle_special_or_operator(ctx, current_char);
	else
		status = handle_default_char_append(ctx, current_char);
	if (status == FAILURE)
		return (FAILURE);
	++ctx->str_ptr;
	return (SUCCESS);
}

int	read_line_and_extend_stream(t_token_stream *stream, t_msvar *msvar)
{
	char	*input_str;
	int		status;

	input_str = readline("> ");
	if (!input_str)
		return (FAILURE);
	status = tokenizer_arr_append(stream, input_str, msvar);
	free(input_str);
	return (status);
}
