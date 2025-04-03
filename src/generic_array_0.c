/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_array_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakim <chakim@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:45:08 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/30 15:58:03 by chakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_array.h"
#include <libft.h>
#include <stdlib.h>
#include "minishell.h"

size_t	gen_arr_len(void **arr)
{
	size_t	len;

	len = 0;
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
	size_t	i;

	i = 0;
	if (del_func)
		while (arr[i])
			del_func(arr[i++]);
	free(arr);
}

void	destroy_void_arr(void **arr, void (*del_func)(void *))
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	if (del_func)
		while (arr[i])
			del_func(arr[i++]);
	free(arr);
}

// Be aware before use this function, all data was must shallow copied.
void	clear_gen_arr(t_gen_arr *arr)
{
	if (!arr)
		return ;
	arr->data[0] = NULL;
	arr->length = 0;
}
