/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:53:55 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/15 23:34:03 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include "minishell.h"
#include "buffer.h"

/*
ms_getcwd - Retrieve the absolute pathname of the current working directory.

DESCRIPTION
This function returns a null-terminated string containing the absolute pathname
of the calling process's current working directory. It dynamically allocates
memory for the pathname using a `t_buf` buffer structure, which it resizes as
necessary to accommodate the entire path.

The function repeatedly calls `getcwd` with an internal buffer, increasing the
buffer size exponentially until `getcwd` succeeds or an error occurs.
Upon successful retrieval, the buffer is resized to fit the exact length of the
pathname, and the internal buffer is returned to the caller.

In case of an error (e.g., memory allocation failure, excessively long path),
the function returns `NULL`.

RETURN
On success: A pointer to a null-terminated string containing the absolute
pathname of the current working directory
On failure: `NULL`

NOTES
The returned string is dynamically allocated and must be freed proplerly
to avoid memory leaks.
If an error occurs during buffer allocation or reallocation, the function
ensures that all allocated resources are properly freed before returning `NULL`.
The function may return `NULL` if the buffer size exceeds the range of `size_t`
and not fitted null-terminated string if last reallocation fail
s.
*/
char	*ms_getcwd(t_buf *buf)
{
	while (!getcwd(buf->buffer, buf->capacity))
	{
		if (buf->capacity > (size_t)(-1) >> 1)
			return (NULL);
		if (realloc_buf(buf, buf->capacity << 1))
			return (NULL);
	}
	return (ft_strdup(buf->buffer));
}
