/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:15:41 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/05 20:21:15 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "buffer.h"
#include <libft.h>
#include <stdlib.h>

#define WITHOUT_QUOTE	0
#define SINGLE_QUOTE	1
#define DOUBLE_QUOTE	2

int	append_buf(t_buf *buf, char c)
{
	if (buf->capacity < buf->length + 2)
	{
		if (buf->capacity > (size_t)(-1) >> 1)
			return (FAILURE);
		if (realloc_buf(buf, buf->capacity << 1))
			return (FAILURE);
	}
	buf->buffer[buf->length] = c;
	++buf->length;
	buf->buffer[buf->length] = '\0';
	return (SUCCESS);
}

int	set_mod(int *mode, char c)
{
	if (c == '\'')
	{
		if (*mode == DOUBLE_QUOTE)
			return (FAILURE);
		else if (*mode == SINGLE_QUOTE)
			*mode = WITHOUT_QUOTE;
		else if (*mode == WITHOUT_QUOTE)
			*mode = SINGLE_QUOTE;
		return (SUCCESS);
	}
	else if (c == '\"')
	{
		if (*mode == SINGLE_QUOTE)
			return (FAILURE);
		else if (*mode == DOUBLE_QUOTE)
			*mode = WITHOUT_QUOTE;
		else if (*mode == WITHOUT_QUOTE)
			*mode = DOUBLE_QUOTE;
		return (SUCCESS);
	}
	return (FAILURE);
}

char	*get_path_name(char *str)
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

size_t	expand_dollar_sign(t_buf *buf, char *str, char **envp)
{
	char	*env_name;
	size_t	result;

	++str;
	if (*str == '?')
	{
		cat_buf(buf, "EXIT_STATUS");
		result = 2;
	}
	else if (ft_isalpha(*str) || *str == '_')
	{
		env_name = get_path_name(str);
		cat_buf(buf, ms_getenv(env_name, envp));
		result = ft_strlen(env_name) + 1;
		free(env_name);
	}
	else
	{
		append_buf(buf, '$');
		result = 1;
	}
	return (result);
}

char	*expand(char *str, char **envp)
{
	int		quote_mode;
	t_buf	*buf;

	quote_mode = WITHOUT_QUOTE;
	buf = create_buf();
	if (!buf)
		return (NULL);
	while (*str)
	{
		if (set_mod(&quote_mode, *str))
		{
			if (quote_mode != SINGLE_QUOTE && *str == '$')
				str += expand_dollar_sign(buf, str, envp);
			else
				append_buf(buf, *str++);
		}
		else
			++str;
	}
	return (detach_buf(buf));
}
