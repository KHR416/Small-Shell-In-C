/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/06 01:30:34 by wchoe            ###   ########.fr       */
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
		for (size_t i = 0; data[i]; ++i)
		{
			cat_buf(*buf, data[i]);
			append_buf(*buf, '*');
		}
		destroy_glob_data(data);
		append_token_list(list, TOKEN_LITERAL, detach_buf(*buf), free);
		*buf = create_buf();
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

t_token_list	*tokenizer_test(char *str, t_msvar *msvar)
{
	t_token_list	*list = create_token_list();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();
	t_gen_arr		*arr = create_gen_arr();
	int				flag = 0;

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
				if (flag)
				{
					expand_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
			}
			else if (*str == '<')
			{
				if (flag)
				{
					expand_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
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
				if (flag)
				{
					expand_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
				if (*(str + 1) == '>')
				{
					append_token_list(list, TOKEN_APPEND_REDIRECT, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_OUTPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '*')
			{
				append_gen_arr(arr, detach_buf(buf), NULL);
				buf = create_buf();
				flag = 1;
			}
			else if (*str == '|')
			{
				if (flag)
				{
					expand_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
				append_token_list(list, TOKEN_PIPE, NULL, NULL);
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
	if (flag)
	{
		expand_glob(list, &buf, &arr);
		flag = 0;
	}
	else if (buf->length)
	{
		append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
		buf = NULL;
	}
	destroy_buf(buf);
	destroy_gen_arr(arr, NULL);
	return (list);
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

t_token_list	*tokenizer_test_glob(char *str, t_msvar *msvar)
{
	t_token_list	*list = create_token_list();
	t_quote_mode	mode = WITHOUT_QUOTE;
	t_buf			*buf = create_buf();
	t_gen_arr		*arr = create_gen_arr();
	int				flag = 0;

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
				if (flag)
				{
					insert_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
			}
			else if (*str == '<')
			{
				if (flag)
				{
					insert_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
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
				if (flag)
				{
					insert_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
				if (*(str + 1) == '>')
				{
					append_token_list(list, TOKEN_APPEND_REDIRECT, NULL, NULL);
					++str;
				}
				else
					append_token_list(list, TOKEN_OUTPUT_REDIRECT, NULL, NULL);
			}
			else if (*str == '*')
			{
				append_gen_arr(arr, detach_buf(buf), NULL);
				buf = create_buf();
				flag = 1;
			}
			else if (*str == '|')
			{
				if (flag)
				{
					insert_glob(list, &buf, &arr);
					flag = 0;
				}
				else if (buf->length)
				{
					append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
					buf = create_buf();
				}
				append_token_list(list, TOKEN_PIPE, NULL, NULL);
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
	if (flag)
	{
		insert_glob(list, &buf, &arr);
		flag = 0;
	}
	else if (buf->length)
	{
		append_token_list(list, TOKEN_LITERAL, detach_buf(buf), free);
		buf = NULL;
	}
	destroy_buf(buf);
	destroy_gen_arr(arr, NULL);
	return (list);
}
