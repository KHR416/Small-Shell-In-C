/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:57:31 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/15 17:20:37 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

ssize_t	putstrn(const char *str, size_t n)
{
	if (write(1, str, n) == -1)
		return (-1);
	else
		return (n);
}

ssize_t	my_putchar(unsigned char c)
{
	return (write(1, &c, 1));
}

ssize_t	my_putnbr(int i)
{
	unsigned int	u;
	ssize_t			temp;

	if (i < 0)
	{
		if (my_putchar('-') == -1)
			return (-1);
		u = -i;
	}
	else
		u = i;
	temp = my_putunbr(u);
	if (temp == -1)
		return (-1);
	return (temp + (i < 0));
}

ssize_t	my_putptr(void *ptr)
{
	ssize_t	temp;

	if (ptr == NULL)
		return (putstrn("(nil)", 5));
	else
	{
		if (putstrn("0x", 2) == -1)
			return (-1);
		temp = my_putunbr_hex((size_t)ptr, LOWER_CASE);
		if (temp == -1)
			return (-1);
		return (temp + 2);
	}
}

ssize_t	my_putstr(const char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}
