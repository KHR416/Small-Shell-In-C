/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:29:24 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/14 23:32:52 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

ssize_t	my_putunbr(unsigned int u)
{
	ssize_t	result;
	ssize_t	temp;

	result = 0;
	if (u > 9)
	{
		temp = my_putunbr(u / 10);
		if (temp == -1)
			return (-1);
		result += temp;
		temp = my_putunbr(u % 10);
		if (temp == -1)
			return (-1);
		result += temp;
	}
	else if (my_putchar(u + '0') == -1)
		return (-1);
	else
		++result;
	return (result);
}

ssize_t	my_putunbr_hex(size_t x, int case_flag)
{
	ssize_t			result;
	ssize_t			temp;
	unsigned char	a;

	result = 0;
	if (case_flag == UPPER_CASE)
		a = 'A';
	else
		a = 'a';
	if (x > 15)
	{
		temp = my_putunbr_hex(x / 16, case_flag);
		if (temp == -1)
			return (-1);
		result += temp;
		temp = my_putunbr_hex(x % 16, case_flag);
		if (temp == -1)
			return (-1);
		result += temp;
	}
	else if (x > 9 && my_putchar(x - 10 + a) == -1)
		return (-1);
	else if (x <= 9 && my_putchar(x + '0') == -1)
		return (-1);
	return (result + (x <= 15));
}
