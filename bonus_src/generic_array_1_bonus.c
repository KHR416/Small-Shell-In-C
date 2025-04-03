/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_array_1.c                                  :+:      :+:    :+:   */
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

void	destroy_gen_arr(t_gen_arr *arr, void (*del_func)(void *))
{
	destroy_void_arr(arr->data, del_func);
	free(arr);
}

int	realloc_gen_arr(t_gen_arr *arr, size_t new_cap)
{
	void	*temp;

	temp = ft_realloc(arr->data, arr->capacity * \
		sizeof(void *), new_cap * sizeof(void *));
	if (!temp)
		return (FAILURE);
	arr->data = temp;
	arr->capacity = new_cap;
	return (SUCCESS);
}

int	append_gen_arr(t_gen_arr *dest, void *src, void *(*dup_func)(void *))
{
	void	*temp;

	while (dest->length + 2 > dest->capacity)
		if (realloc_gen_arr(dest, dest->capacity << 1))
			return (FAILURE);
	if (dup_func)
	{
		temp = dup_func(src);
		if (!temp)
			return (FAILURE);
		dest->data[dest->length] = temp;
	}
	else
		dest->data[dest->length] = src;
	++dest->length;
	dest->data[dest->length] = NULL;
	return (SUCCESS);
}

void	**detach_gen_arr(t_gen_arr *arr)
{
	void	**data;

	realloc_gen_arr(arr, arr->length + 1);
	data = arr->data;
	free(arr);
	return (data);
}
