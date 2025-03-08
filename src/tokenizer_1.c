/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/07 22:45:20 by wchoe            ###   ########.fr       */
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
		env_name = get_env_name(str);
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

t_token_stream	*tokenizer_arr(char *str, t_msvar *msvar)
{
	t_token_stream	*stream = create_token_stream();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();
	t_gen_arr		*arr = create_gen_arr();
	int				flag_glob = 0;

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
			else if (*str == '*')
			{
				append_gen_arr(arr, buf->buffer, ft_strdup_wrap);
				clear_buf(buf);
				flag_glob = 1;
			}
			else if (*str == ' ')
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
			else if (*str == '<')
			{
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
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
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
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
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
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
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_AND_OPERATOR, NULL);
				++str;
			}
			else if (*str == '(')
			{
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_PARENTHESIS_OPEN, NULL);
			}
			else if (*str == ')')
			{
				flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
				append_token_stream(stream, TOKEN_PARENTHESIS_CLOSE, NULL);
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
	flush_bufs_arr_with_expand(stream, buf, arr, &flag_glob);
	destroy_buf(buf);
	destroy_gen_arr(arr, NULL);
	return (stream);
}

void	destroy_glob_data(char **data)
{
	size_t	i = 0;
	while (data[i])
		free(data[i++]);
	free(data);
}

void	destroy_glob_data_wrap(void *data)
{
	destroy_glob_data(data);
}

int	expand_glob(t_token_list *list, t_buf **buf, t_gen_arr **arr)
{
	char	**data, **glob;
	
	if ((*buf)->length)
	{
		append_gen_arr(*arr, detach_buf(*buf), NULL);
		*buf = create_buf();
	}
	data = (char **)detach_gen_arr(*arr);
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
		destroy_glob_data(data);
		append_token_list(list, TOKEN_LITERAL, detach_buf(temp), free);
	}
	else
	{
		destroy_glob_data(data);
		for (size_t i = 0; glob[i]; ++i)
			append_token_list(list, TOKEN_LITERAL, glob[i], free);
		free(glob);
	}
	*arr = create_gen_arr();
	return (SUCCESS);
}

int	insert_glob(t_token_list *list, t_buf **buf, t_gen_arr **arr)
{
	if ((*buf)->length)
	{
		append_gen_arr(*arr, detach_buf(*buf), NULL);
		*buf = create_buf();
	}
	append_token_list(list, TOKEN_GLOB, detach_gen_arr(*arr), destroy_glob_data_wrap);
	*arr = create_gen_arr();
	return (SUCCESS);
}

int flush_bufs(t_token_list *list, t_buf **buf, t_gen_arr **arr, int *flag_glob)
{
	if (*flag_glob)
	{
		insert_glob(list, buf, arr);
		*flag_glob = 0;
	}
	else if ((*buf)->length)
	{
		append_token_list(list, TOKEN_LITERAL, detach_buf(*buf), free);
		*buf = create_buf();
	}
	return (SUCCESS);
}

t_token_list	*tokenizer_list(char *str, t_msvar *msvar)
{
	t_token_list	*list = create_token_list();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();
	t_gen_arr		*arr = create_gen_arr();
	int				flag_glob = 0;

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
			else if (*str == '*')
			{
				append_gen_arr(arr, detach_buf(buf), NULL);
				buf = create_buf();
				flag_glob = 1;
			}
			else if (*str == ' ')
				flush_bufs(list, &buf, &arr, &flag_glob);
			else if (*str == '<')
			{
				flush_bufs(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '<')
				{
					append_token_list(list, TOKEN_HERE_DOC, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_INPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '>')
			{
				flush_bufs(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '>')
				{
					append_token_list(list, TOKEN_APPEND_REDIRECT, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_OUTPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '|')
			{
				flush_bufs(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '|')
				{
					append_token_list(list, TOKEN_OR_OPERATOR, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_PIPE, NULL, NULL);
			}
			else if (*str == '&' && *(str + 1) == '&')
			{
				flush_bufs(list, &buf, &arr, &flag_glob);
				append_token_list(list, TOKEN_AND_OPERATOR, NULL, NULL);
				++str;
			}
			else if (*str == '(' || *str == ')')
			{
				flush_bufs(list, &buf, &arr, &flag_glob);
				if (*str == '(')
					append_token_list(list, TOKEN_PARENTHESIS_OPEN, NULL, NULL);
				else
					append_token_list(list, TOKEN_PARENTHESIS_CLOSE, NULL, NULL);
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
	flush_bufs(list, &buf, &arr, &flag_glob);
	destroy_buf(buf);
	destroy_gen_arr(arr, NULL);
	return (list);
}

int flush_bufs_with_expand(t_token_list *list, t_buf **buf, t_gen_arr **arr, int *flag_glob)
{
	if (*flag_glob)
	{
		expand_glob(list, buf, arr);
		*flag_glob = 0;
	}
	else if ((*buf)->length)
	{
		append_token_list(list, TOKEN_LITERAL, detach_buf(*buf), free);
		*buf = create_buf();
	}
	return (SUCCESS);
}

t_token_list	*tokenizer_list_expand(char *str, t_msvar *msvar)
{
	t_token_list	*list = create_token_list();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();
	t_gen_arr		*arr = create_gen_arr();
	int				flag_glob = 0;

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
			else if (*str == '*')
			{
				append_gen_arr(arr, detach_buf(buf), NULL);
				buf = create_buf();
				flag_glob = 1;
			}
			else if (*str == ' ')
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
			else if (*str == '<')
			{
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '<')
				{
					append_token_list(list, TOKEN_HERE_DOC, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_INPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '>')
			{
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '>')
				{
					append_token_list(list, TOKEN_APPEND_REDIRECT, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_OUTPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '|')
			{
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
				if (*(str + 1) == '|')
				{
					append_token_list(list, TOKEN_OR_OPERATOR, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_PIPE, NULL, NULL);
			}
			else if (*str == '&' && *(str + 1) == '&')
			{
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
				append_token_list(list, TOKEN_AND_OPERATOR, NULL, NULL);
				++str;
			}
			else if (*str == '(' || *str == ')')
			{
				flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
				if (*str == '(')
					append_token_list(list, TOKEN_PARENTHESIS_OPEN, NULL, NULL);
				else
					append_token_list(list, TOKEN_PARENTHESIS_CLOSE, NULL, NULL);
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
	flush_bufs_with_expand(list, &buf, &arr, &flag_glob);
	destroy_buf(buf);
	destroy_gen_arr(arr, NULL);
	return (list);
}
