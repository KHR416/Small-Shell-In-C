/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:47:23 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 13:47:26 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	while (('\t' <= *nptr && *nptr <= '\r') || *nptr == ' ')
		++nptr;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		++nptr;
	}
	result = 0;
	while (ft_isdigit(*nptr))
		result = 10 * result + *nptr++ - '0';
	return (sign * result);
}
