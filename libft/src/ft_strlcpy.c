/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:59:45 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 13:59:47 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	idx = 0;
	while (idx < src_len && idx < size - 1)
	{
		dst[idx] = src[idx];
		++idx;
	}
	dst[idx] = '\0';
	return (src_len);
}
