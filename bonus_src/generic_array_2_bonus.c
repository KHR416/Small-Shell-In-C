/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_array_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:44:50 by chakim            #+#    #+#             */
/*   Updated: 2025/03/30 15:59:11 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_array.h"
#include <libft.h>
#include <stdlib.h>
#include "minishell.h"

static int	calculate_new_capacity(t_gen_arr *dest, size_t add_len)
{
	size_t	new_cap;

	new_cap = dest->capacity;
	if (dest->length + add_len + 1 > dest->capacity)
	{
		new_cap = dest->capacity << 1;
		while (dest->length + add_len + 1 > new_cap)
			new_cap <<= 1;
		if (realloc_gen_arr(dest, new_cap))
			return (FAILURE);
	}
	return (SUCCESS);
}

int	cat_gen_arr(t_gen_arr *dest, void **src, void *(*dup_func)(void *))
{
	size_t	i;
	size_t	src_len;
	void	*temp;

	src_len = gen_arr_len(src);
	if (calculate_new_capacity(dest, src_len) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < src_len)
	{
		if (dup_func)
		{
			temp = dup_func(src[i]);
			if (!temp)
				return (FAILURE);
			dest->data[dest->length + i] = temp;
		}
		else
			dest->data[dest->length + i] = src[i];
		++i;
	}
	dest->length += src_len;
	dest->data[dest->length] = NULL;
	return (SUCCESS);
}
