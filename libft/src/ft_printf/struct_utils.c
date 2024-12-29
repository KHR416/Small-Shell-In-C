/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:23:01 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_conv(t_conversion *conv)
{
	size_t	idx;

	idx = -1;
	while (++idx < 5)
		conv->flags[idx] = 0;
	conv->field = 0;
	conv->precision = -1;
}

void	init_lens(t_conv_len *lengths)
{
	lengths->len = 0;
	lengths->prefix_len = 0;
	lengths->nspace = 0;
	lengths->nzero = 0;
}

unsigned int	total_len(const t_conv_len lengths)
{
	return (lengths.len + lengths.prefix_len + lengths.nspace + lengths.nzero);
}
