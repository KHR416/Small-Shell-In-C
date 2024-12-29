/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:05:13 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:05:16 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		++len;
	while (n != 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*nptr;
	unsigned int	temp;
	size_t			len;

	if (n == 0)
		return (ft_strdup("0"));
	len = count_len(n);
	temp = n;
	if (n < 0)
		temp = -n;
	nptr = (char *)malloc(len + 1);
	if (nptr == NULL)
		return (NULL);
	nptr[len--] = '\0';
	while (temp > 0)
	{
		nptr[len--] = temp % 10 + '0';
		temp /= 10;
	}
	if (n < 0)
		*nptr = '-';
	return (nptr);
}
