/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:59:41 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:00:00 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (src_len + size);
	idx = 0;
	while (idx < src_len && idx < size - dst_len - 1)
	{
		dst[dst_len + idx] = src[idx];
		++idx;
	}
	dst[dst_len + idx] = '\0';
	return (dst_len + src_len);
}
