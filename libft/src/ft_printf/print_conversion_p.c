/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_p_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:27:17 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

static unsigned int	get_len_ptr(size_t x)
{
	unsigned int	len;

	if (x == 0)
		return (5);
	len = 0;
	while (x)
	{
		++len;
		x /= 16;
	}
	return (len + 2);
}

static ssize_t	put_nbr_ptr_with_flags(t_conversion conv, t_conv_len lengths, \
	void *ptr)
{
	if (has_flag_minus(conv.flags))
	{
		if (my_putptr(ptr) == -1 \
			|| putcharn(' ', lengths.nspace) == -1)
			return (-1);
	}
	else
	{
		if (putcharn(' ', lengths.nspace) == -1 \
			|| my_putptr(ptr) == -1)
			return (-1);
	}
	return (total_len(lengths));
}

ssize_t	print_conversion_p(const t_conversion conv, void *ptr)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = get_len_ptr((size_t)ptr);
	if ((unsigned int)conv.field > lengths.len)
		lengths.nspace = conv.field - lengths.len;
	return (put_nbr_ptr_with_flags(conv, lengths, ptr));
}
