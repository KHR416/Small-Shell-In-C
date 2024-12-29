/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:53:55 by wchoe             #+#    #+#             */
/*   Updated: 2024/12/29 23:15:47 by wchoe            ###   ########.fr       */
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
	size_t	size;

	size = BUFFER_SIZE;
	while (1)
	{
		buf = (char *)malloc(BUFFER_SIZE);
		if (!buf)
			return (NULL);
		if (getcwd(buf, size))
			break ;
		free(buf);
		if (size << 1 > (size_t)-1)
			return (NULL);
		size <<= 1;
	}
	path = ft_strdup(buf);
	free(buf);
	return (path);
}
