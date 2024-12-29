/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversion_s_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:35:39 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"

static unsigned int	get_len(int precision, const char *str)
{
	if (str == NULL && precision >= 0 && precision < 6)
		return (0);
	else if (str == NULL)
		return (6);
	else if (precision >= 0)
		return ((unsigned int)my_min(precision, ft_strlen(str)));
	else
		return (ft_strlen(str));
}

static	ssize_t	print_str_with_flags_precision(const char *str, \
	const t_conversion conv, t_conv_len lengths)
{
	if (has_flag_minus(conv.flags))
	{
		if (putstrn(str, lengths.len) == -1 \
			|| putcharn(' ', lengths.nspace) == -1)
			return (-1);
	}
	else
	{
		if (putcharn(' ', lengths.nspace) == -1 \
			|| putstrn(str, lengths.len) == -1)
			return (-1);
	}
	return (total_len(lengths));
}

ssize_t	print_conversion_s(const t_conversion conv, const char *str)
{
	t_conv_len	lengths;

	init_lens(&lengths);
	lengths.len = get_len(conv.precision, str);
	if ((unsigned int)conv.field > lengths.len)
		lengths.nspace = conv.field - lengths.len;
	if (str == NULL)
		str = "(null)";
	return (print_str_with_flags_precision(str, conv, lengths));
}
