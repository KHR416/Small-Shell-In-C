/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:00:15 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 15:22:46 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	idx_big;
	size_t	len_big;
	size_t	len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	idx_big = 0;
	len_big = ft_strlen(big);
	while (idx_big + len_little <= len_big && idx_big + len_little <= len)
	{
		if (ft_strncmp(big + idx_big, little, len_little) == 0)
			return ((char *)big + idx_big);
		++idx_big;
	}
	return (NULL);
}
