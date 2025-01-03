/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:53:55 by wchoe             #+#    #+#             */
/*   Updated: 2025/01/03 15:55:21 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>
#include "minishell.h"

/*
This function returns a null-terminated string containing an absolute pathname
of the calling process.
In case of an error, `NULL` is returned.

To avoid memory leaks, the returned string should be properly freed.
*/
char	*ms_getcwd(void)
{
	char	*path;
	char	*buf;
	void	*temp;
	size_t	size;

	size = BUFFER_SIZE;
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (getcwd(buf, size))
			break ;
		if (size > (size_t)(-1) >> 1)
			return (free(buf), NULL);
		temp = ft_realloc(buf, size, size << 1);
		if (!temp)
			return (free(buf), NULL);
		buf = temp;
		size <<= 1;
	}
	path = ft_strdup(buf);
	free(buf);
	return (path);
}
