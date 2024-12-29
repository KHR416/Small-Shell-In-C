/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:01:53 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 14:02:54 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*temp_s;

	if (ft_strlen(s1) == 0)
		return (ft_calloc(1, 1));
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1) != NULL)
		++s1;
	if (!*s1)
		return (ft_calloc(1, 1));
	temp_s = s1 + ft_strlen(s1);
	while (temp_s > s1 && ft_strrchr(set, *temp_s) != NULL)
		--temp_s;
	return (ft_substr(s1, 0, temp_s - s1 + 1));
}
