/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:36:51 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/14 22:23:29 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "minishell.h"
#include <libft.h>
#include <stdlib.h>

/*
detach_buf - Detach the internal buffer from a `t_buf` structure

DESCRIPTION
This function detaches the internal buffer from the provided `t_buf` structure.
It attempts to resize the internal buffer to exactly fit the current data using
`realloc_buf`. After resizing, the function frees the `t_buf` structure itself
and returns the internal buffer pointer.

If resizing fails, the original internal buffer remains unchanged and is still
returned to ensure data integrity.

RETURN
On success to resize, a pointer to the null-terminated internal buffer.
Otherwise, the original internal buffer is still returned.

NOTES
The returned buffer must be properly freed by the caller using `free` to prevent
memory leaks.
After calling this function, the `t_buf` structure is no longer valid and should
not be used.
*/
char	*detach_buf(t_buf *buf)
{
	char	*str;

	realloc_buf(buf, ft_strlen(buf->buffer) + 1);
	str = buf->buffer;
	free(buf);
	return (str);
}

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
