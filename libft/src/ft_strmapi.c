/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:05:34 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:05:35 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*mapped;
	size_t	len;
	size_t	idx;

	len = ft_strlen(s);
	mapped = (char *)malloc(len + 1);
	if (mapped == NULL)
		return (NULL);
	idx = (size_t)-1;
	while (++idx < len)
		mapped[idx] = f(idx, s[idx]);
	mapped[idx] = '\0';
	return (mapped);
}
