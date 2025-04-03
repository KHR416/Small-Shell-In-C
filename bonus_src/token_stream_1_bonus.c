/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stream_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:06:42 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/25 19:50:51 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"
#include "buffer.h"
#include "token.h"
#include <stdlib.h>

t_token	*read_token_stream(t_token_stream *stream)
{
	t_token	*ret;

	if (stream->offset > stream->len)
		return (NULL);
	ret = stream->arr + stream->offset++;
	return (ret);
}

t_token	*peek_token_stream(t_token_stream *stream, ssize_t offset)
{
	if ((ssize_t)stream->offset + offset > (ssize_t)stream->len
		|| (ssize_t)stream->offset + offset < 0)
		return (NULL);
	return (stream->arr + stream->offset + offset);
}
