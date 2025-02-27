/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/02/27 08:57:39 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

char	*get_path_name_with_equal_sign(char *str)
{
	char	*name;
	size_t	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		++len;
	name = malloc(len + 2);
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, len + 2);
	ft_strlcat(name, "=", len + 2);
	return (name);
}

size_t	expand_dollar_sign(t_buf *buf, char *str, t_msvar *msvar)
{
	char	*env_name;
	size_t	padding;

	++str;
	if (*str == '?')
	{
		if (msvar->exit_status >= 100)
			append_buf(buf, msvar->exit_status / 100 + '0');
		if (msvar->exit_status >= 10)
			append_buf(buf, msvar->exit_status / 10 % 10 + '0');
		append_buf(buf, msvar->exit_status % 10 + '0');
		padding = 1;
	}
	else if (ft_isalpha(*str) || *str == '_')
	{
		env_name = get_path_name_with_equal_sign(str);
		cat_buf(buf, ms_getenv(env_name, msvar->envp));
		padding = ft_strlen(env_name) - 1;
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
	if (buf->length || !stream->len)
	{
		append_token_stream(stream, TOKEN_LITERAL, detach_buf(buf));
		buf = NULL;
	}
	destroy_buf(buf);
	return (stream);
}
