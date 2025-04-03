/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/31 08:47:45 by chakim           ###   ########.fr       */
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

char	*get_env_name(char *str)
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

int	flush_bufs_arr_with_expand_ctx(t_tokenizer_context *ctx)
{
	int		status;
	char	*buf_content;

	status = SUCCESS;
	if (ctx->flag_glob)
	{
		status = expand_glob_with_arr(ctx);
		ctx->flag_glob = 0;
	}
	else if (ctx->msvar->buf->length > 0)
	{
		buf_content = ft_strdup(ctx->msvar->buf->buffer);
		if (!buf_content)
			return (FAILURE);
		if (append_token_stream(ctx->stream, TOKEN_LITERAL, buf_content))
		{
			free(buf_content);
			return (FAILURE);
		}
		clear_buf(ctx->msvar->buf);
	}
	return (status);
}

size_t	handle_dollar_qmark(t_msvar *msvar)
{
	int	status_val;

	status_val = msvar->exit_status;
	if (status_val >= 100)
		append_buf(msvar->buf, status_val / 100 + '0');
	if (status_val >= 10)
		append_buf(msvar->buf, status_val / 10 % 10 + '0');
	append_buf(msvar->buf, status_val % 10 + '0');
	return (1);
}

size_t	handle_dollar_var(t_tokenizer_context *ctx, const char *env_val)
{
	while (*env_val)
	{
		if (*env_val == ' ')
			flush_bufs_arr_with_expand_ctx(ctx);
		else
			append_buf(ctx->msvar->buf, *env_val);
		++env_val;
	}
	return (0);
}

size_t	handle_dollar_variable_expansion(t_tokenizer_context *ctx)
{
	char	*env_name;
	char	*expanded_val;
	size_t	padding;

	env_name = get_env_name(ctx->str_ptr + 1);
	if (!env_name)
		return (0);
	expanded_val = ms_getenv(env_name, ctx->msvar->envp);
	padding = ft_strlen(env_name);
	if (expanded_val)
		handle_dollar_var(ctx, expanded_val);
	free(env_name);
	return (padding);
}
