/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:20:42 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/14 23:07:01 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	my_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

ssize_t	putcharn(unsigned char c, size_t n)
{
	size_t	temp_n;

	temp_n = n;
	while (temp_n--)
	{
		if (my_putchar(c) == -1)
			return (-1);
	}
	return (n);
}
