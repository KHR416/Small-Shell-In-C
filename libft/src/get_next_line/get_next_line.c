/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchoe <wchoe@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:59:42 by wchoe             #+#    #+#             */
/*   Updated: 2024/10/23 16:13:44 by wchoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_buf_vari	b_v = {.eob = 1};
	t_new_line			nl;

	if (fd < 0 || (b_v.eob && gnl_get(NEW_BUFFER, fd, &b_v, NULL)))
		return (NULL);
	nl.len = (size_t)gnl_get(LINE_LEN, fd, &b_v, NULL);
	if (b_v.buf[b_v.st_idx + nl.len - 1] != '\n')
	{
		if (gnl_get(EXTRACTED_NEW_LINE, fd, &b_v, &nl))
			return (free(nl.str), NULL);
	}
	else if (gnl_get(NEW_LINE, fd, &b_v, &nl))
		return (NULL);
	return (nl.str);
}
