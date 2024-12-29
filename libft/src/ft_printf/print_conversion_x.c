/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_x_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:27:49 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

static unsigned int	get_len_hex(const t_conversion conv, unsigned int x)
{
	unsigned int	len;

	if (conv.precision == 0 && x == 0)
		return (0);
	else if (x == 0)
		return (1);
	len = 0;
	while (x)
	{
		++len;
		x /= 16;
	}
	return (len);
}

static	ssize_t	put_nbr_hex(const t_conversion conv, \
	unsigned int x, int case_flag)
{
	if (conv.precision || x)
		return (my_putunbr_hex(x, case_flag));
	else
		return (0);
}

static ssize_t	print_x_flags_and_precision(const t_conversion conv, \
	unsigned int x, const t_conv_len lengths, int case_flag)
{
	char	*pref;

	if (case_flag == UPPER_CASE)
		pref = "0X";
	else
		pref = "0x";
	if (has_flag_minus(conv.flags))
	{
		if ((has_flag_hash(conv.flags) && x != 0 && my_putstr(pref) == -1) \
			|| putcharn('0', lengths.nzero) == -1)
			return (-1);
	}
	else
	{
		if (putcharn(' ', lengths.nspace) == -1 \
			|| (has_flag_hash(conv.flags) && x != 0 && my_putstr(pref) == -1) \
			|| putcharn('0', lengths.nzero) == -1)
			return (-1);
	}
	if (put_nbr_hex(conv, x, case_flag) == -1 \
		|| (has_flag_minus(conv.flags) && putcharn(' ', lengths.nspace) == -1))
		return (-1);
	return (total_len(lengths));
}

ssize_t	print_conversion_x(const t_conversion c, unsigned int x, int case_flag)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = get_len_hex(c, x);
	if (c.precision >= 0 && (unsigned int)c.precision > lengths.len)
		lengths.nzero = (unsigned int)c.precision - lengths.len;
	lengths.prefix_len = 2 * (has_flag_hash(c.flags) && x != 0);
	if ((unsigned int)c.field \
		> lengths.len + lengths.prefix_len + lengths.nzero)
		lengths.nspace = (unsigned int)c.field \
			- lengths.len - lengths.prefix_len - lengths.nzero;
	if (c.precision < 0 && !has_flag_minus(c.flags) && has_flag_zero(c.flags))
	{
		lengths.nzero = lengths.nspace;
		lengths.nspace = 0;
	}
	return (print_x_flags_and_precision(c, x, lengths, case_flag));
}
