/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:58:02 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:48:50 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)s1;
	mem2 = (unsigned char *)s2;
	while (n--)
	{
		if (*mem1 != *mem2)
			return (*mem1 - *mem2);
		++mem1;
		++mem2;
	}
	return (0);
}
