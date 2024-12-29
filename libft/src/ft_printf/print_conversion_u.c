/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_u_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:27:17 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

static unsigned int	get_len(const t_conversion conv, unsigned int u)
{
	unsigned int	len;

	if (!(conv.precision || u))
		return (0);
	else if (!u)
		return (1);
	len = 0;
	while (u)
	{
		++len;
		u /= 10;
	}
	return (len);
}

static ssize_t	put_unbr(const t_conversion conv, unsigned int u)
{
	if (!(conv.precision || u))
		return (0);
	else
		return (my_putunbr(u));
}

static ssize_t	put_unbr_with_flags(const t_conversion conv, \
	const t_conv_len lengths, unsigned int u)
{
	if (has_flag_minus(conv.flags))
	{
		if (putcharn('0', lengths.nzero) == -1 \
			|| put_unbr(conv, u) == -1 \
			|| putcharn(' ', lengths.nspace) == -1)
			return (-1);
	}
	else
	{
		if (putcharn(' ', lengths.nspace) == -1 \
			|| putcharn('0', lengths.nzero) == -1 \
			|| put_unbr(conv, u) == -1)
			return (-1);
	}
	return (total_len(lengths));
}

ssize_t	print_conversion_u(const t_conversion c, unsigned int u)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = get_len(c, u);
	if (c.precision >= 0 && (unsigned int)c.precision > lengths.len)
		lengths.nzero = (unsigned int)c.precision - lengths.len;
	if ((unsigned int)c.field > lengths.nzero + lengths.len)
		lengths.nspace = (unsigned int)c.field - lengths.nzero - lengths.len;
	if (c.precision < 0 && !has_flag_minus(c.flags) && has_flag_zero(c.flags))
	{
		lengths.nzero = lengths.nspace;
		lengths.nspace = 0;
	}
	return (put_unbr_with_flags(c, lengths, u));
}
