/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:01:59 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:02:01 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (len == 0 || s_len <= start)
		return (ft_calloc(1, 1));
	else
	{
		if (s_len - start < len)
			substr_len = s_len - start;
		else
			substr_len = len;
	}
	substr = (char *)malloc(substr_len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}
