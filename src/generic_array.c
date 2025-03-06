/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:45:08 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/06 00:35:34 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_array.h"
#include <libft.h>
#include <stdlib.h>
#include "minishell.h"

size_t	gen_arr_len(void **arr)
{
	size_t	len = 0;
	
	while (arr[len])
		++len;
	return (len);
}

t_gen_arr	*create_gen_arr(void)
{
	t_gen_arr	*arr;

	arr = malloc(sizeof(t_gen_arr));
	if (!arr)
		return (NULL);
	arr->data = malloc(ARR_DEFAULT_CAP * sizeof(void *));
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->data[0] = NULL;
	arr->capacity = ARR_DEFAULT_CAP;
	arr->length = 0;
	return (arr);
}

void	destroy_arr(void **arr, void (*del_func)(void *))
{
	size_t	i = 0;

	if (del_func)
		while (arr[i])
		del_func(arr[i++]);
	free(arr);
}

void	clear_gen_arr(t_gen_arr *arr, void (*del_func)(void *))
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	if (del_func)
		while (arr->data[i])
			del_func(arr->data[i++]);
	arr->data[0] = NULL;
	arr->length = 0;
}

void	destroy_gen_arr(t_gen_arr *arr, void (*del_func)(void *))
{
	clear_gen_arr(arr, del_func);
	if (arr)
		free(arr->data);
	free(arr);
}

int		realloc_gen_arr(t_gen_arr *arr, size_t new_cap)
{
	void	*temp;

	temp = ft_realloc(arr->data, arr->capacity * sizeof(void *), new_cap * sizeof(void *));
	if (!temp)
		return (FAILURE);
	arr->data = temp;
	arr->capacity = new_cap;
	return (SUCCESS);
}

int		cat_gen_arr(t_gen_arr *dest, void **src, void *(*dup_func)(void *))
{
	size_t	i;
	size_t	src_len;
	size_t	new_cap;
	void	*temp;

	src_len = gen_arr_len(src);
	if (dest->length + src_len + 1 > dest->capacity)
	{
		new_cap = dest->capacity << 1;
		while (dest->length + src_len + 1 > new_cap)
			new_cap <<= 1;
		if (realloc_gen_arr(dest, new_cap))
			return (FAILURE);
	}
	if (dup_func)
	{
		i = 0;
		while (i < src_len)
		{
			temp = dup_func(src[i]);
			if (!temp)
			{
				// Exception
			}
			dest->data[dest->length + i++] = temp;
		}
	}
	else
	{
		i = 0;
		while (i < src_len)
		{
			dest->data[dest->length + i] = src[i];
			++i;
		}
	}
	dest->length += src_len;
	dest->data[dest->length] = NULL;
	return (SUCCESS);
}

int		append_gen_arr(t_gen_arr *dest, void *src, void *(*dup_func)(void *))
{
	void	*temp;

	while (dest->length + 2 > dest->capacity)
		if (realloc_gen_arr(dest, dest->capacity << 1))
			return (FAILURE);
	if (dup_func)
	{
		temp = dup_func(src);
		if (!temp)
		{
			// Exception
		}
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
