/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:56:19 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 13:57:20 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	count = 0;
	while (str1[count] && str2[count] && count < n)
	{
		if (str1[count] == str2[count])
			++count;
		else
			return (str1[count] - str2[count]);
	}
	if (count == n)
		return (0);
	return (str1[count] - str2[count]);
}
