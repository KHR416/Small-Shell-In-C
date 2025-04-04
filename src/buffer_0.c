/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 19:23:04 by wchoe             #+#    #+#             */
/*   Updated: 2025/04/04 17:34:41 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "minishell.h"
#include <libft.h>
#include <stdlib.h>

/*
create_buf - Allocates and initializes a new buffer.

DESCRIPTION
This function allocates memory for a `t_buf` structure and its internal data
buffer with an initial capacity defined by `BUFFER_SIZE`. It initializes the
buffer's length to zero and sets the first character of the buffer to the
null terminator to represent an empty string.

RETURN
This function returns pointer to the newly created `t_buf` structure on success
or returns `NULL` if memory allocation for either the structure or the internal
buffer fails.

NOTES
Every buffer created by this function must be properly deallocated using
the `destroy_buf` or `detach_buf` function to prevent memory leaks. When using
the `detach_buf` function, the returned internal buffer must be freed
separately.
*/
t_buf	*create_buf(void)
{
	t_buf	*buf;

	buf = malloc(sizeof(t_buf));
	if (!buf)
		return (NULL);
	buf->buffer = malloc(BUFFER_SIZE);
	if (!buf->buffer)
	{
		free(buf);
		return (NULL);
	}
	*buf->buffer = '\0';
	buf->length = 0;
	buf->capacity = BUFFER_SIZE;
	return (buf);
}

/*
destroy_buf - Frees the given buffer

DESCRIPTION
This function releases all memory allocated by the `create_buf` function,
including the internal data buffer and the `t_buf` structure itself.
If the provided `buf` is `NULL`, the function performs no action.

RETURN
None

NOTES
Every buffer created by `create_buf` must be properly deallocated using
this function to prevent memory leaks. After calling this function, assigning
`NULL` to the buffer pointer is recommended to prevent accidental double
freeing.
*/
void	destroy_buf(t_buf *buf)
{
	if (!buf)
		return ;
	free(buf->buffer);
	free(buf);
}

/*
clear_buf - Clears the given buffer

DESCRIPTION
This function resets the buffer to an empty state by setting the first character
of the internal data buffer to the null terminator (`'\0') and updating the
buffer's length to zero.

RETURN
None

NOTES
This function may cause segmentation fault if `buf` is `NULL`.
This function does not free any memory; it only resets the buffer's content and
length. And the buffer's capacity remains unchanged.
*/
void	clear_buf(t_buf *buf)
{
	*buf->buffer = '\0';
	buf->length = 0;
}

/*
realloc_buf - Reallocate the internal buffer of a `t_buf` structure.

DESCRIPTION
This function reallocates the internal buffer of the given `buf` to a
new capacity specified by `new_cap`. It utilizes `ft_realloc` to perform
the memory reallocation. If the reallocation is successful, the buffer's
capacity is updated to `new_cap`. If the reallocation fails, the original
internal buffer remains unchanged, ensuring the integrity of the existing data.

RETURN
`SUCCESS` (0) on successful reallocation.
`FAILURE` (1) if the reallocation fails.

NOTES
This function may cause segmentation fault if `buf` is `NULL`.
This function can be used to both expand and shrink the internal buffer as
needed.
*/
int	realloc_buf(t_buf *buf, size_t new_cap)
{
	void	*temp;

	temp = ft_realloc(buf->buffer, buf->capacity, new_cap);
	if (!temp)
		return (FAILURE);
	buf->buffer = temp;
	buf->capacity = new_cap;
	return (SUCCESS);
}

/*
cat_buf - Concatenate a string to the buffer

DESCRIPTION
This function appends the given string `str` to the internal buffer of the
`t_buf` structure `buf`. After successful concatenation, the `length` member of
`t_buf` is updated to reflect the new length of the data. It ensures that the
internal buffer remains null-terminated after concatenation. If the current
capacity of the buffer is insufficient to accommodate the concatenated data,
the buffer is reallocated to a larger size to fit the new data.
If `str` is `NULL`, This function do nothing and return `SUCCESS`.

RETURN
`SUCCESS` (0) on successful concatenation or `str` is `NULL`
`FAILURE` (1) if memory reallocation fails.

NOTES
This function may cause segmentation fault if `buf` is `NULL`.
This function can also be used to copy a string into the buffer. It is
recommended to use this function immediately after calling `clear_buf`
if you intend to overwrite the buffer.
*/
int	cat_buf(t_buf *buf, char *str)
{
	size_t	len;
	size_t	new_cap;

	if (!str)
		return (SUCCESS);
	len = ft_strlen(str);
	if (buf->capacity < buf->length + len + 1)
	{
		new_cap = buf->capacity;
		while (new_cap < buf->length + len + 1)
		{
			if (new_cap > (size_t)(-1) >> 1)
				return (FAILURE);
			new_cap <<= 1;
		}
		if (realloc_buf(buf, new_cap))
			return (FAILURE);
	}
	ft_strlcat(buf->buffer, str, buf->capacity);
	buf->length += len;
	return (SUCCESS);
}
