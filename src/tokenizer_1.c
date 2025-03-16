/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/16 00:40:18 by wchoe            ###   ########.fr       */
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

int	flush_bufs_arr_with_expand(t_token_stream *stream, t_buf *buf, t_gen_arr *arr, int *flag_glob);

size_t	expand_dollar_sign(t_token_stream *stream, char *str, t_msvar *msvar, t_gen_arr *arr, int *flag_glob)
{
	char	*env_name;
	size_t	padding;
	char	*expanded;

	++str;
	if (*str == '?')
	{
		if (msvar->exit_status >= 100)
			append_buf(msvar->buf, msvar->exit_status / 100 + '0');
		if (msvar->exit_status >= 10)
			append_buf(msvar->buf, msvar->exit_status / 10 % 10 + '0');
		append_buf(msvar->buf, msvar->exit_status % 10 + '0');
		padding = 1;
	}
	else if (ft_isalpha(*str) || *str == '_')
	{
		env_name = get_env_name(str);
		expanded = ms_getenv(env_name, msvar->envp);
		if (expanded)
		{
			for (; *expanded; ++expanded)
			{
				if (*expanded == ' ')
					flush_bufs_arr_with_expand(stream, msvar->buf, arr, flag_glob);
				else
					append_buf(msvar->buf, *expanded);
			}
		}
		padding = ft_strlen(env_name);
		free(env_name);
	}
	else
	{
		append_buf(msvar->buf, '$');
		padding = 0;
	}
	return (padding);
}

void	*ft_strdup_wrap(void *str)
{
	return (ft_strdup(str));
}

int	expand_glob_with_arr(t_token_stream *stream, t_buf *buf, t_gen_arr *arr)
{
	char	**data, **glob;
	
	if (buf->length)
	{
		append_gen_arr(arr, buf->buffer, ft_strdup_wrap);
		clear_buf(buf);
	}
	data = malloc((arr->length + 1) * sizeof(void *));
	ft_memcpy(data, arr->data, (arr->length + 1) * sizeof(void *));
	clear_gen_arr(arr);
	glob = ms_glob(data);
	if (!glob)
	{
		// Exception
	}
	if (!*glob)
	{
		free(glob);
		t_buf	*temp = create_buf();
		for (size_t i = 0; data[i]; ++i)
		{
			cat_buf(temp, data[i]);
			append_buf(temp, '*');
		}
		destroy_void_arr((void **)data, free);
		append_token_stream(stream, TOKEN_LITERAL, detach_buf(temp));
	}
	else
	{
		destroy_void_arr((void **)data, free);
		for (size_t i = 0; glob[i]; ++i)
			append_token_stream(stream, TOKEN_LITERAL, glob[i]);
		free(glob);
	}
	return (SUCCESS);
}

int	flush_bufs_arr_with_expand(t_token_stream *stream, t_buf *buf, t_gen_arr *arr, int *flag_glob)
{
	if (*flag_glob)
	{
		expand_glob_with_arr(stream, buf, arr);
		*flag_glob = 0;
	}
	else if (buf->length)
	{
		append_token_stream(stream, TOKEN_LITERAL, ft_strdup(buf->buffer));
		clear_buf(buf);
	}
	return (SUCCESS);
}

int	tokenizer_arr_append(t_token_stream *stream, char *str, t_msvar *msvar)
{
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_gen_arr		*arr = create_gen_arr();
	int				flag_glob = 0;

	clear_buf(msvar->buf);
	if (msvar->command_buf->length)
		append_buf(msvar->command_buf, ' ');
	cat_buf(msvar->command_buf, str);
	while (*str)
	{
		if (mode == WITHOUT_QUOTE)
		{
			if (*str == '\'')
				mode = SINGLE_QUOTE;
			else if (*str == '"')
				mode = DOUBLE_QUOTE;
			else if (*str == '$')
				str += expand_dollar_sign(stream, str, msvar, arr, &flag_glob);
			else if (*str == '*')
			{
				append_gen_arr(arr, msvar->buf->buffer, ft_strdup_wrap);
				clear_buf(msvar->buf);
				flag_glob = 1;
			}
			else if (*str == ' ')
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
			else if (*str == '<')
			{
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
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
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
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
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
				if (*(str + 1) == '|')
				{
					append_token_stream(stream, TOKEN_OR_OPERATOR, NULL);
					++str;
				}
				else
					append_token_stream(stream, TOKEN_PIPE, NULL);
			}
			else if (*str == '&' && *(str + 1) == '&')
			{
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_AND_OPERATOR, NULL);
				++str;
			}
			else if (*str == '(')
			{
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_PARENTHESIS_OPEN, NULL);
			}
			else if (*str == ')')
			{
				flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_PARENTHESIS_CLOSE, NULL);
			}
			else
				append_buf(msvar->buf, *str);
			++str;
		}
		else if (mode == SINGLE_QUOTE)
		{
			if (*str == '\'')
				mode = WITHOUT_QUOTE;
			else
				append_buf(msvar->buf, *str);
			++str;
		}
		else
		{
			if (*str == '"')
				mode = WITHOUT_QUOTE;
			else if (*str == '$')
				str += expand_dollar_sign(stream, str, msvar, arr, &flag_glob);
			else
				append_buf(msvar->buf, *str);
			++str;
		}
	}
	flush_bufs_arr_with_expand(stream, msvar->buf, arr, &flag_glob);
	destroy_gen_arr(arr, NULL);
	return (SUCCESS);
}
#ifdef MEMCHECK
#include <string.h>
static char	*readline(const char *prompt)
{
	char	buf[1024];
	printf("%s", prompt);
	if (!fgets(buf, 1024, stdin))
		return (NULL);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';
	return (strdup(buf));
}
#else
# include <readline/readline.h>
#endif	// MEMCHECK

int	read_and_append(t_token_stream *stream, t_msvar *msvar)
{
	char	*str = readline("> ");
	
	if (!str)
		return (FAILURE);
	int	status = tokenizer_arr_append(stream, str, msvar);
	free(str);
	return (status);
}