/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:38:23 by wchoe             #+#    #+#             */
/*   Updated: 2024/11/04 17:52:56 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils_bonus.h"
#include <stdarg.h>

static int	print_conversion(const t_conversion conv, va_list arg_list)
{
	if (conv.specifier == 'c')
		return (print_conversion_c(conv, va_arg(arg_list, int)));
	else if (conv.specifier == 'd' || conv.specifier == 'i')
		return (print_conversion_d(conv, va_arg(arg_list, int)));
	else if (conv.specifier == 'p')
		return (print_conversion_p(conv, va_arg(arg_list, void *)));
	else if (conv.specifier == 's')
		return (print_conversion_s(conv, va_arg(arg_list, const char *)));
	else if (conv.specifier == 'u')
		return (print_conversion_u(conv, va_arg(arg_list, unsigned int)));
	else if (conv.specifier == 'x')
		return (print_conversion_x(conv, va_arg(arg_list, unsigned int), \
			LOWER_CASE));
	else if (conv.specifier == 'X')
		return (print_conversion_x(conv, va_arg(arg_list, unsigned int), \
			UPPER_CASE));
	else if (conv.specifier == '%')
		return (my_putchar('%'));
	else
		return (-1);
}

static int	parse_and_print(const char *format, va_list arg_list, \
	const char **location)
{
	int				temp;
	t_conversion	conv;

	init_conv(&conv);
	*location = parse_conversion(format, &conv);
	if (!**location || ft_strchr(SPECIFIER_SET, **location) == NULL)
		return (-1);
	temp = print_conversion(conv, arg_list);
	return (temp);
}

static int	ft_vprintf(const char *format, va_list arg_list)
{
	int				count;
	int				temp;
	const char		*location;

	count = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if (my_putchar(*format++) == -1)
				return (-1);
			++count;
		}
		else
		{
			temp = parse_and_print(format, arg_list, &location);
			if (temp == -1)
				return (-1);
			count += temp;
			format = location + 1;
		}
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		result;

	va_start(arg_list, format);
	result = ft_vprintf(format, arg_list);
	va_end(arg_list);
	return (result);
}
