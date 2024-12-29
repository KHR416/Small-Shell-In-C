/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:46:57 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/26 13:54:36 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*allocated;

	if (nmemb != 0 && size > (size_t)-1 / nmemb)
		return (NULL);
	allocated = (unsigned char *)malloc(nmemb * size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, nmemb * size);
	return (allocated);
}
