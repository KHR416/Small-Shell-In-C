/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversion_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:33:53 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:54:08 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

// Set flags, field, and precision, and return the location of the specifier or
// last read loaction if there is no specifier.
// The 'format' parameter must be the location of '%'.
// The 'flags', 'field', 'precision' and 'specifier' which are the member of
// 'conv' parameter must be initialized as 0, 0, -1, 0.
// Conversion format: %[flags][field][precision][specifier]
char	*parse_conversion(const char *format, t_conversion *conv)
{
	++format;
	while (*format && ft_strchr(FLAG_SET, *format))
		conv->flags[ft_strchr(FLAG_SET, *format++) - FLAG_SET] = 1;
	while (ft_isdigit(*format))
		conv->field = 10 * conv->field + *format++ - '0';
	if (*format == '.')
	{
		conv->precision = 0;
		++format;
		while (ft_isdigit(*(format)))
			conv->precision = 10 * conv->precision + *format++ - '0';
	}
	if (*format && ft_strchr(SPECIFIER_SET, *format))
		conv->specifier = *format;
	return ((char *)format);
}
