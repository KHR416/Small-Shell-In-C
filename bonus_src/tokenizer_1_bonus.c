/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/03 21:06:54 by wchoe            ###   ########.fr       */
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

size_t	expand_dollar_sign(t_tokenizer_context *ctx)
{
	size_t	padding;
	char	next_char;

	next_char = *(ctx->str_ptr + 1);
	padding = 0;
	if (next_char == '?')
		padding = handle_dollar_qmark(ctx->msvar);
	else if (ft_isalpha(next_char) || next_char == '_')
		padding = handle_dollar_variable_expansion(ctx);
	else
		append_buf(ctx->msvar->buf, '$');
	return (padding);
}

size_t	handle_dollar_variable_expansion_quoted(t_msvar *msvar,
	char *current_str_pos)
{
	char	*env_name;
	char	*expanded_val;
	size_t	padding;

	env_name = get_env_name(current_str_pos + 1);
	if (!env_name)
		return (0);
	expanded_val = ms_getenv(env_name, msvar->envp);
	if (expanded_val)
		cat_buf(msvar->buf, expanded_val);
	padding = ft_strlen(env_name);
	free(env_name);
	return (padding);
}

size_t	expand_dollar_sign_with_quote(t_msvar *msvar, char *str_ptr)
{
	size_t	padding;
	char	next_char;

	next_char = *(str_ptr + 1);
	padding = 0;
	if (next_char == '?')
		padding = handle_dollar_qmark(msvar);
	else if (ft_isalpha(next_char) || next_char == '_')
	{
		padding = handle_dollar_variable_expansion_quoted(msvar, \
			str_ptr);
		if (padding == 0 && (ft_isalpha(next_char) || next_char == '_'))
			return (0);
	}
	else
		append_buf(msvar->buf, '$');
	return (padding);
}

int	handle_glob_no_match(t_token_stream *stream, char **data)
{
	t_buf	*temp_buf;
	size_t	i;
	char	*final_token;

	temp_buf = create_buf();
	if (!temp_buf)
		return (FAILURE);
	i = 0;
	while (data[i])
	{
		if (*data[i])
			cat_buf(temp_buf, data[i]);
		else
			append_buf(temp_buf, '*');
		++i;
	}
	final_token = detach_buf(temp_buf);
	if (append_token_stream(stream, TOKEN_LITERAL, final_token))
	{
		free(final_token);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_glob_match(t_token_stream *stream, \
	char **glob_results)
{
	size_t	i;
	char	*copied_str;

	i = 0;
	while (glob_results[i])
	{
		copied_str = ft_strdup(glob_results[i]);
		if (!copied_str)
			return (FAILURE);
		if (append_token_stream(stream, TOKEN_LITERAL, copied_str))
		{
			free(copied_str);
			return (FAILURE);
		}
		++i;
	}
	return (SUCCESS);
}
