/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:10:15 by wchoe             #+#    #+#             */
/*   Updated: 2025/03/07 22:32:10 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_ARRAY_H
# define GENERIC_ARRAY_H
# define ARR_DEFAULT_CAP	4
# include <unistd.h>

typedef struct s_generic_array
{
	size_t	length;
	size_t	capacity;
	void	**data;
}	t_gen_arr;

void		destroy_arr(void **arr, void (*del_func)(void *));
t_gen_arr	*create_gen_arr(void);
void		destroy_gen_arr(t_gen_arr *arr, void (*del_func)(void *));
void		clear_gen_arr(t_gen_arr *arr);
int			realloc_gen_arr(t_gen_arr *arr, size_t new_cap);
int			cat_gen_arr(t_gen_arr *dest, void **src, void *(*dup_func)(void *));
int			append_gen_arr(t_gen_arr *dest, void *src, void *(*dup_func)(void *));
void		**detach_gen_arr(t_gen_arr *arr);
void		destroy_void_arr(void **arr, void (*del_func)(void *));
#endif