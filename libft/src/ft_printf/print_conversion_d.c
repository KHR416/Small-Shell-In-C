/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_d_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:27:17 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

static unsigned int	get_len_nbr_wo_sign(const t_conversion conv, int i)
{
	unsigned int	len;
	unsigned int	u;

	if (conv.precision == 0 && i == 0)
		return (0);
	else if (i == 0)
		return (1);
	if (i < 0)
		u = -i;
	else
		u = i;
	len = 0;
	while (u)
	{
		++len;
		u /= 10;
	}
	return (len);
}

static ssize_t	put_nbr_without_sign(const t_conversion conv, int i)
{
	unsigned int	u;

	if (i < 0)
		u = -i;
	else
		u = i;
	if (conv.precision == 0 && i == 0)
		return (0);
	return (my_putunbr(u));
}

static ssize_t	put_nbr_with_sign_and_zero(const t_conversion conv, \
	const t_conv_len lengths, int i)
{
	if (i < 0 && my_putchar('-') == -1)
		return (-1);
	else if (i >= 0 && has_flag_plus(conv.flags) && my_putchar('+') == -1)
		return (-1);
	else if (i >= 0 && !has_flag_plus(conv.flags) \
		&& has_flag_space(conv.flags) && my_putchar(' ') == -1)
		return (-1);
	if (putcharn('0', lengths.nzero) == -1
		|| put_nbr_without_sign(conv, i) == -1)
		return (-1);
	return (lengths.prefix_len + lengths.nzero + lengths.len);
}

static ssize_t	put_nbr_with_flags(const t_conversion conv, \
	const t_conv_len lengths, int i)
{
	if (has_flag_minus(conv.flags))
	{
		if (put_nbr_with_sign_and_zero(conv, lengths, i) == -1 \
			|| putcharn(' ', lengths.nspace) == -1)
			return (-1);
	}
	else
	{
		if (putcharn(' ', lengths.nspace) == -1
			|| put_nbr_with_sign_and_zero(conv, lengths, i) == -1)
			return (-1);
	}
	return (total_len(lengths));
}

ssize_t	print_conversion_d(const t_conversion c, int i)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = get_len_nbr_wo_sign(c, i);
	if (c.precision >= 0 && (unsigned int)c.precision > lengths.len)
		lengths.nzero = (unsigned int)c.precision - lengths.len;
	lengths.prefix_len = (i < 0 \
		|| has_flag_plus(c.flags) || has_flag_space(c.flags));
	if ((unsigned int)c.field \
		> lengths.nzero + lengths.len + lengths.prefix_len)
		lengths.nspace = (unsigned int)c.field \
			- lengths.nzero - lengths.len - lengths.prefix_len;
	if (c.precision < 0 && !has_flag_minus(c.flags) && has_flag_zero(c.flags))
	{
		lengths.nzero = lengths.nspace;
		lengths.nspace = 0;
	}
	return (put_nbr_with_flags(c, lengths, i));
}
