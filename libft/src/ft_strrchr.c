/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:55:57 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 13:56:02 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	idx;
	char	ch;

	idx = ft_strlen(s);
	ch = (char)c;
	while (idx)
	{
		if (s[idx] == ch)
			return ((char *)s + idx);
		else
			--idx;
	}
	if (*s == ch)
		return ((char *)s);
	else
		return (NULL);
}
