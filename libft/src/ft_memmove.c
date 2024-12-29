/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:52:56 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:56:02 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;

	if (dest > src)
		while (n--)
			*((unsigned char *)dest + n) = *((unsigned char *)src + n);
	else
	{
		temp_dest = (unsigned char *)dest;
		while (n--)
			*temp_dest++ = *(unsigned char *)src++;
	}
	return (dest);
}
