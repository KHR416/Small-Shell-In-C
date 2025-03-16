/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/09 14:59:06 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>
#define TOKEN_STREAM_INITIAL_CAP	4

t_token_stream	*create_token_stream(void)
{
	t_token_stream	*stream;

	stream = malloc(sizeof(t_token_stream));
	if (!stream)
		return (NULL);
	stream->arr = malloc(sizeof(t_token) * TOKEN_STREAM_INITIAL_CAP);
	if (!stream->arr)
	{
		free(stream);
		return (NULL);
	}
	stream->arr[0].type = TOKEN_NONE;
	stream->len = 0;
	stream->offset = 0;
	stream->cap = TOKEN_STREAM_INITIAL_CAP;
	return (stream);
}

void	destroy_token_stream(t_token_stream *stream)
{
	size_t	i;

	i = 0;
	while (stream->arr[i].type != TOKEN_NONE)
		free(stream->arr[i++].data);
	free(stream->arr);
	free(stream);
}

int	realloc_token_stream(t_token_stream *stream, size_t new_cap)
{
	t_token	*temp;

	temp = ft_realloc(stream->arr, sizeof(t_token) * stream->cap, sizeof(t_token) * new_cap);
	if (!temp)
		return (FAILURE);
	stream->arr = temp;
	stream->cap = new_cap;
	return (SUCCESS);
}

int	append_token_stream(t_token_stream *stream, t_token_type type, char *data)
{
	if (stream->cap < stream->len + 2 && realloc_token_stream(stream, stream->cap << 1))
		return (FAILURE);
	stream->arr[stream->len].type = type;
	if (type == TOKEN_LITERAL)
		stream->arr[stream->len].data = data;
	else
		stream->arr[stream->len].data = NULL;
	stream->arr[++stream->len].type = TOKEN_NONE;
	return (SUCCESS);
}
