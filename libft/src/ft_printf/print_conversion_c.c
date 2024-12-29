/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_c_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:52:26 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

ssize_t	print_conversion_c(const t_conversion conv, unsigned char c)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = 1;
	if (conv.field)
		lengths.nspace = conv.field - 1;
	if (has_flag_minus(conv.flags))
	{
		if (my_putchar(c) == -1 || putcharn(' ', lengths.nspace) == -1)
			return (-1);
	}
	else
		if (putcharn(' ', lengths.nspace) == -1 || my_putchar(c) == -1)
			return (-1);
	return (total_len(lengths));
}
